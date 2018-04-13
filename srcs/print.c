/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:24:53 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/13 12:47:18 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_st(t_data *data, t_symbol_64 **stab, int length)
{
	int i;
	char *s;

	if (data->multi && !data->fat64 && !data->libstatic)
	{
		ft_putchar('\n');
		ft_putstr(data->filename);
		ft_putstr(":\n");
	}//sauf quand fat ??
	i = 0;
	while (stab[i])
	{
		if (stab[i]->type == 'U')
		{
			if (length == 16)
				ft_putstr("                 ");
			else
				ft_putstr("         ");
		}
		else
		{
			s = value_to_str(stab[i]->value, "0123456789abcdef", length);
			ft_putstr(s);
			ft_putchar(' ');
			free(s);
		}
		ft_putchar(stab[i]->type);
		ft_putchar(' ');
		ft_putendl(stab[i]->name);
		i++;
	}
}

void		print_arch(t_data *data)
{
	cpu_type_t cpu;

	cpu = to_swap(((struct mach_header*)(data->ptr + data->offset))->cputype, data);
	if (data->fat > 1)
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

char		*value_to_str(uint64_t value, char *hex, int i)
{
	char		*str;
	uint32_t	r;

	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		ft_putendl("Probleme allocation");
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
	return (str);
}
