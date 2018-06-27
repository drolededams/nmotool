/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:12:33 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/27 13:07:15 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

void		print_64(t_data *data)
{
	struct section_64	*sec;
	uint32_t			offset;

	sec = (struct section_64*)data->sec;
	offset = (data->libstatic || data->obj) ? 0 : to_swap(sec->offset, data);
	offset_check_sec(data, offset, to_swap(sec->size, data));
	if (data->fat && !data->libstatic && !data->error)
		print_arch(data, sec, offset);
	else if (data->multi && !data->fat && !data->libstatic && !data->error)
	{
		ft_putstr(data->filename);
		ft_putstr(":\n");
		print_normal_64(data, sec, offset);
	}
	else if (!data->libstatic && !data->fat && !data->error)
	{
		ft_putstr(data->filename);
		ft_putendl(":");
		print_normal_64(data, sec, offset);
	}
	else if (data->libstatic && !data->error)
		print_normal_64(data, sec, offset);
}

void		print_normal_64(t_data *data, struct section_64 *sec,
	uint32_t offset)
{
	unsigned long	i;
	int				j;
	uint32_t		len;
	char			*str;

	i = 0;
	ft_putendl("Contents of (__TEXT,__text) section");
	while ((i * 16) < to_swap(sec->size, data))
	{
		j = 0;
		print_addr((uint64_t)(offset + (i * 16) + data->exe),
			"0123456789abcdef", 16);
		ft_putchar('\t');
		str = ft_strnew(47);
		len = ((i * 16) + 15 < to_swap(sec->size, data)) ?
			16 : to_swap(sec->size, data) - (i * 16);
		print_content((char*)(data->ptr + to_swap(sec->offset, data) +
			i * 16 + data->offset), "0123456789abcdef", str, len);
		ft_putendl(str);
		ft_memdel((void**)&str);
		i++;
	}
}

void		print_arch(t_data *data, struct section_64 *sec, uint32_t offset)
{
	cpu_type_t cpu;

	cpu = to_swap(((struct mach_header*)(data->ptr + data->offset))->cputype,
		data);
	if (data->nfat > 1)
	{
		ft_putstr(data->filename);
		ft_putchar(' ');
		ft_putstr("(architecture ");
		if (cpu == CPU_TYPE_POWERPC)
			ft_putendl("ppc):");
		else if (cpu == CPU_TYPE_I386)
			ft_putendl("i386):");
		print_normal_64(data, sec, offset);
	}
	else
	{
		ft_putstr(data->filename);
		ft_putendl(":");
		print_normal_64(data, sec, offset);
	}
}

void		print_char(unsigned char c, char *hex, char *dest)
{
	char		*str;
	uint32_t	r;
	int			i;

	i = 3;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		ft_putendl("Probleme allocation");
	else
	{
		str[i--] = '\0';
		str[i] = ' ';
		while (c)
		{
			i--;
			r = c % 16;
			str[i] = hex[r];
			c /= 16;
		}
		while (i > 0)
			str[i--] = '0';
		ft_strcat(dest, str);
		ft_memdel((void**)&str);
	}
}

void		print_content(char *str, char *hex, char *dest, uint32_t n)
{
	uint32_t		r;
	uint32_t		i;
	int				j;
	unsigned char	c;

	i = 0;
	while (i < n)
	{
		c = str[i];
		dest[i * 3 + 2] = ' ';
		j = 1;
		while (c)
		{
			r = c % 16;
			dest[i * 3 + j] = hex[r];
			c /= 16;
			j--;
		}
		while (j >= 0)
			dest[i * 3 + j--] = '0';
		i++;
	}
	dest[i * 3] = '\0';
}
