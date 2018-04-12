/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:00:12 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/12 20:11:28 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	nm_process(t_data *data)
{
	if (is_static(data))
		static_lib_process(data);
	else
		mach_o_process(data);
}

int		offset_check(t_data *data, size_t size)
{
	if (data->offset + size < data->filesize)
	{
		data->error = 0;
		return (1);
	}
	if (data->offset + size > data->filesize)
		data->error = 1;
	return (0);
}

void	mach_o_process(t_data *data)
{
	uint32_t magic;

	if (offset_check(data, sizeof(uint32_t)))
	{
		magic = *(uint32_t*)(data->ptr + data->offset);
		if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
			parse_mach_o_64(data);
		else if (magic == MH_MAGIC || magic == MH_CIGAM)
			parse_mach_o_32(data);
		else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
			parse_fat(data);
		else
			data->error = 4;
	}
}

void	fat_process(struct fat_header *header, t_data *data)
{
	struct fat_arch		*fa;
	size_t				total_offset;
	unsigned long			i;

	i = 0;
	data->swap = 0;
	if (header->magic == FAT_CIGAM)
		data->swap = 1;
	fa = (void*)(header + 1);
	data->offset = to_swap(fa->offset, data);
	total_offset = sizeof(struct fat_header);
	data->fat = to_swap(header->nfat_arch, data);
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
