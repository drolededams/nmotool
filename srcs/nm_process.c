/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:00:12 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/10 17:06:14 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	nm_process(t_data *data)
{
	if (is_static_lib(data))
		static_lib_process(data);
	else
		mach_o_process(data);
}

void	static_lib_process(t_data *data)
{
	if (header_lib_check(data))
	{
		
	}
	ft_putendl("Bad header lib");
}

int		header_lib_check(t_data *data)
{
	if (data->filesize <= data->offset + 68)
	{
		if ((char)(data->ptr + data->offset + 66) == '`' && (char)(data->ptr + data->offset + 67) == '\n')
			return (1);
	}
	return (0);
}

int		is_static(t_data *data)
{
	if (data->filesize >= 8 + data->offset && ft_strncmp(data->ptr, "!<arch>\n", 8) == 0)
		return (1);
	return (0);
}

void	mach_o_process(t_data *data)
{
	uint32_t magic;

	magic = *(uint32_t*)(data->ptr + data->offset);
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		parse_mach_o_64(data);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		parse_mach_o_32(data);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		parse_fat(data);
}

void		parse_fat(t_data *data)
{
	struct fat_header	*header;
	struct fat_arch		*fa;
	size_t				total_offset;
	unsigned long			i;
	uint32_t			magic;

	magic = *(uint32_t*)(data->ptr + data->offset);
	if (magic == FAT_CIGAM)
		data->swap = 1;
	if (sizeof(struct fat_header) <= data->filesize)
	{
		header = (struct fat_header*)data->ptr;
		if ((sizeof(struct fat_header) + sizeof(struct fat_arch)) <= data->filesize)
		{
			i = 0;
			fa = (void*)(header + 1);
			data->offset = to_swap(fa->offset, data);
			total_offset = sizeof(struct fat_header);
			while(i < to_swap(header->nfat_arch, data) && (cpu_type_t)(to_swap(fa->cputype, data)) != CPU_TYPE_X86_64)
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
				mach_o_process(data);
			}
			else
				fat_process(header, data);
		}
	}
}

void fat_process(struct fat_header *header, t_data *data)
{
	struct fat_arch		*fa;
	size_t				total_offset;
	unsigned long			i;

	i = 0;
	data->swap = 0;
	data->fat = 1;
	if (header->magic == FAT_CIGAM)
		data->swap = 1;
	fa = (void*)(header + 1);
	data->offset = to_swap(fa->offset, data);
	total_offset = sizeof(struct fat_header);
	while (i < to_swap(header->nfat_arch, data))
	{
		parse_mach_o_32(data);
		if (total_offset + sizeof(struct fat_arch) <= data->filesize)
		{
			fa = (void*)fa + sizeof(struct fat_arch);
			total_offset += sizeof(struct fat_arch);
			data->offset = to_swap(fa->offset, data);
		}
		data->swap = 0;
		if (header->magic == FAT_CIGAM)
			data->swap = 1;
		i++;
	}
	data->fat = 0;
}

unsigned long	to_swap(unsigned long value, t_data *data)
{
	if(data->swap)
		return (swap_bit(value));
	return (value);
}

unsigned long	swap_bit(unsigned long value)
{
	return (((value << 24) & 0xFF000000) | ((value << 8) & 0xFF0000) | ((value >> 8) & 0xFF00) | ((value >> 24) & 0xFF));
}
