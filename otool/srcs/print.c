/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:12:33 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/18 18:42:37 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void		print_64(t_data *data)
{
	unsigned long i;
	int j;
	struct section_64 *sec;

	sec = (struct section_64*)data->sec;
	offset_check(data, to_swap(sec->offset, data) + to_swap(sec->size, data));
	if (data->multi && !data->fat && !data->libstatic && !data->error)
	{
		ft_putchar('\n');
		ft_putstr(data->filename);
		ft_putstr(":\n");
	}
	i = 0;
	ft_putstr(data->filename);
	ft_putendl(":");
	ft_putendl("Contents of (__TEXT,__text) section");
	while ((i * 16) < to_swap(sec->size, data))
	{
		j = 0;
		print_addr((uint64_t)(sec->offset + (i * 16) + 0x100000000), "0123456789abcdef", 16);
		ft_putchar('\t');
		while (j < 16 && ((i * 16) + j) < to_swap(sec->size, data))
		{
			print_addr((uint64_t)(*(char*)(data->ptr + sec->offset + i * 16 + j + data->offset)), "0123456789abcdef", 2);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void		print_32(t_data *data)
{
	unsigned long i;
	int j;
	struct section *sec;

	sec = (struct section*)data->sec;
	offset_check(data, to_swap(sec->offset, data) + to_swap(sec->size, data));
	if (data->multi && !data->fat && !data->libstatic && !data->error)
	{
		ft_putchar('\n');
		ft_putstr(data->filename);
		ft_putstr(":\n");
	}
	i = 0;
	ft_putstr(data->filename);
	ft_putendl(":");
	ft_putendl("Contents of (__TEXT,__text) section");
	while ((i * 16) < to_swap(sec->size, data))
	{
		j = 0;
		print_addr((uint64_t)(sec->offset + (i * 16) + 0x1000), "0123456789abcdef", 8);
		ft_putchar('\t');
		while (j < 16 && ((i * 16) + j) < to_swap(sec->size, data))
		{
			print_addr((uint64_t)(*(char*)(data->ptr + sec->offset + i * 16 + j + data->offset)), "0123456789abcdef", 2);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
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
	ft_putchar('\n');
	ft_putstr(data->filename);
	ft_putchar('(');
	ft_putstr(filename);
	ft_putendl("):");
	ft_memdel((void**)&filename);
}
