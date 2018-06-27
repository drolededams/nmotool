/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_ut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:36:17 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/23 18:38:27 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

int			search_x86_64(t_data *data, struct fat_arch *fa, uint32_t nfat_arch)
{
	size_t			total_offset;
	unsigned long	i;

	total_offset = sizeof(struct fat_header);
	i = 0;
	while (i < to_swap(nfat_arch, data) &&
			(cpu_type_t)(to_swap(fa->cputype, data)) != CPU_TYPE_X86_64)
	{
		if (total_offset + sizeof(struct fat_arch) <= data->filesize)
		{
			fa = (void*)fa + sizeof(struct fat_arch);
			total_offset += sizeof(struct fat_arch);
		}
		i++;
	}
	if (to_swap(fa->cputype, data) == CPU_TYPE_X86_64)
	{
		data->offset = to_swap(fa->offset, data);
		return (1);
	}
	return (0);
}

int			offset_check_sec(t_data *data, uint32_t offset, size_t size)
{
	if (!offset_check(data, size))
		return (0);
	else if (!offset_check(data, offset))
		return (0);
	else if (SIZE_MAX - size < offset)
	{
		data->error = 1;
		return (0);
	}
	else if (!offset_check(data, size + offset))
		return (0);
	else
	{
		data->error = 0;
		return (1);
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
