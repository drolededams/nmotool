/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:12:33 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/19 16:26:05 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void		print_64(t_data *data)
{
	unsigned long i;
	int j;
	struct section_64 *sec;
	uint32_t offset;
	uint32_t len;
	char *str;

	sec = (struct section_64*)data->sec;
	offset = (data->libstatic || data->obj) ? 0 : sec->offset;
	offset_check(data, to_swap(offset, data) + to_swap(sec->size, data));
	if (data->multi && !data->fat && !data->libstatic && !data->error)
	{
		ft_putchar('\n');
		ft_putstr(data->filename);
		ft_putstr(":\n");
	}
	i = 0;
	if (!data->libstatic)
	{
		ft_putstr(data->filename);
		ft_putendl(":");
	}
	ft_putendl("Contents of (__TEXT,__text) section");
	while ((i * 16) < to_swap(sec->size, data))
	{
		j = 0;
		print_addr((uint64_t)(offset + (i * 16) + data->exe), "0123456789abcdef", 16);
		ft_putchar('\t');
		str = ft_strnew(47);
		/*while (j < 16 && ((i * 16) + j) < to_swap(sec->size, data))
		{
			print_char(*(char*)(data->ptr + sec->offset + i * 16 + j + data->offset), "0123456789abcdef", str);
			j++;
		}*/
		len = ((i * 16) + 15 < to_swap(sec->size, data)) ? 16 : to_swap(sec->size, data) - (i * 16);
		print_content((char*)(data->ptr + sec->offset + i * 16 + data->offset), "0123456789abcdef", str, len);
		ft_putendl(str);
		ft_memdel((void**)&str);
		i++;
	}
}

void		print_char(unsigned char c, char *hex, char* dest)
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
		{
			i--;
			str[i] = '0';
		}
		ft_strcat(dest, str);
		ft_memdel((void**)&str);
	}
}

void		print_content(char *str, char *hex, char* dest, uint32_t n)
{
	uint32_t	r;
	uint32_t	i;
	int			j;
	unsigned char		c;

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
		{
			dest[i * 3 + j] = '0';
			j--;
		}
		i++;
	}
	dest[i * 3] = '\0';
}

void		print_32(t_data *data)
{
	unsigned long i;
	int j;
	struct section *sec;
	uint32_t		offset;
	char *str;
	uint32_t len;

	sec = (struct section*)data->sec;
	offset = (data->libstatic || data->obj) ? 0 : sec->offset;
	offset_check(data, to_swap(sec->offset, data) + to_swap(sec->size, data));
	if (data->multi && !data->fat && !data->libstatic && !data->error)
	{
		ft_putchar('\n');
		ft_putstr(data->filename);
		ft_putstr(":\n");
	}
	i = 0;
	if (!data->libstatic)
	{
		ft_putstr(data->filename);
		ft_putendl(":");
	}
	ft_putendl("Contents of (__TEXT,__text) section");
	while ((i * 16) < to_swap(sec->size, data))
	{
		j = 0;
		print_addr((uint64_t)(offset + (i * 16) + data->exe), "0123456789abcdef", 8);
		ft_putchar('\t');
		str = ft_strnew(47);
		/*while (j < 16 && ((i * 16) + j) < to_swap(sec->size, data))
		{
			print_char(*(char*)(data->ptr + sec->offset + i * 16 + j + data->offset), "0123456789abcdef", str);
			j++;
		}*/
		len = ((i * 16) + 15 < to_swap(sec->size, data)) ? 16 : to_swap(sec->size, data) - (i * 16);
		print_content((char*)(data->ptr + sec->offset + i * 16 + data->offset), "0123456789abcdef", str, len);
		ft_putendl(str);
		ft_memdel((void**)&str);
		i++;
	}
}

void		print_addr(uint64_t addr, char *hex, int i)
{
	char		*str;
	uint32_t	r;

	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		ft_putendl("Probleme allocation");
	else
	{
		str[i] = '\0';
		while (addr)
		{
			i--;
			r = addr % 16;
			str[i] = hex[r];
			addr /= 16;
		}
		while (i > 0)
		{
			i--;
			str[i] = '0';
		}
		ft_putstr(str);
		ft_memdel((void**)&str);
	}
}

void		print_lib_name(t_data *data, size_t len)
{
	char *filename;

	filename = ft_strnew(len);
	ft_strncpy(filename, data->ptr + data->offset, len);
	ft_putstr(data->filename);
	ft_putchar('(');
	ft_putstr(filename);
	ft_putendl("):");
	ft_memdel((void**)&filename);
}
