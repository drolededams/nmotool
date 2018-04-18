/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:00:12 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/18 18:52:51 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	ot_process(t_data *data)
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
			parse_mach_o_64(data, magic);
		else if (magic == MH_MAGIC || magic == MH_CIGAM)
			parse_mach_o_32(data, magic);
		else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
			parse_fat(data, magic);
		else
			data->error = 4;
	}
}

void	fat_process(struct fat_header *header, t_data *data)
{
	struct fat_arch		*fa;
	size_t				total_offset;
	unsigned long		i;

	i = 0;
	data->swap = (header->magic == FAT_CIGAM) ? 1 : 0;
	fa = (void*)(header + 1);
	data->offset = to_swap(fa->offset, data);
	total_offset = sizeof(struct fat_header);
	data->nfat = to_swap(header->nfat_arch, data);
	while (i < to_swap(header->nfat_arch, data))
	{
		if (!data->error && offset_check(data, sizeof(uint32_t)))
			parse_mach_o_32(data, *(uint32_t*)(data->ptr + data->offset));
		if (!data->error && total_offset + sizeof(struct fat_arch) <=
				data->filesize)
		{
			fa = (void*)fa + sizeof(struct fat_arch);
			total_offset += sizeof(struct fat_arch);
			data->offset = to_swap(fa->offset, data);
		}
		data->swap = (header->magic == FAT_CIGAM) ? 1 : 0;
		i++;
	}
	data->nfat = 0;
}

void	lib_process(t_data *data)
{
	size_t		len;
	uint32_t	filesize;

	if ((len = filename_lenght(data)))
	{
		if (offset_check(data, 60))
		{
			if (!(filesize = get_filesize(data)))
				ft_putendl_fd("error parse_lib filesize", STDERR_FILENO);
		}
		else
			ft_putendl_fd("error parse_lib offset_check", STDERR_FILENO);
		data->offset += 60;
		if (offset_check(data, len))
		{
			print_lib_name(data, len);
			data->offset += len;
			ot_process(data);
			data->offset += filesize - len;
		}
		else
			ft_putendl_fd("error parse_lib offset_check", STDERR_FILENO);
	}
}
