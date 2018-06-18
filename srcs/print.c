/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:24:53 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/14 20:04:27 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		print_st(t_data *data, t_symbol_64 **stab, int length)
{
	int i;
	int j;

	if (data->multi && !data->fat && !data->libstatic)
	{
		ft_putchar('\n');
		ft_putstr(data->filename);
		ft_putstr(":\n");
	}
	i = 0;
	while (stab[i])
	{
		j = 0;
		if (stab[i]->type == 'U')
			while (j++ <= length)
				ft_putchar(' ');
		else
			print_value(stab[i]->value, "0123456789abcdef", length);
		ft_putchar(stab[i]->type);
		ft_putchar(' ');
		putendl_protect(stab[i]->name, data);
		i++;
	}
}

void		putendl_protect(char *name, t_data *data)
{
	uint64_t	i;
	uint64_t	offset;

	offset = (uint64_t)name - (uint64_t)data->ptr;
	i = 0;
	while (offset + i < data->filesize && name[i])
	{
		ft_putchar(name[i]);
		i++;
	}
	ft_putchar('\n');
}

void		print_arch(t_data *data)
{
	cpu_type_t cpu;

	cpu = to_swap(((struct mach_header*)(data->ptr + data->offset))->cputype,
			data);
	if (data->nfat > 1)
	{
		ft_putchar('\n');
		ft_putstr(data->filename);
		ft_putchar(' ');
		ft_putstr("(for architecture ");
		if (cpu == CPU_TYPE_POWERPC)
			ft_putendl("ppc):");
		else if (cpu == CPU_TYPE_I386)
			ft_putendl("i386):");
	}
	else
	{
		ft_putstr(data->filename);
		ft_putendl(":");
	}
}

void		print_value(uint64_t value, char *hex, int i)
{
	char		*str;
	uint32_t	r;

	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		ft_putendl("Probleme allocation");
	else
	{
		str[i] = '\0';
		while (value)
		{
			i--;
			r = value % 16;
			str[i] = hex[r];
			value /= 16;
		}
		while (i > 0)
		{
			i--;
			str[i] = '0';
		}
		ft_putstr(str);
		ft_putchar(' ');
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
