/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 15:49:27 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/23 15:49:32 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

void	parse_mach_o_64(t_data *data, uint32_t magic)
{
	struct mach_header_64	*header;
	struct load_command		*lc;

	data->swap = (magic == MH_CIGAM_64) ? 1 : 0;
	if (offset_check(data, sizeof(struct mach_header_64)))
	{
		header = (struct mach_header_64*)(data->ptr + data->offset);
		if (offset_check(data, sizeof(struct mach_header_64) +
			sizeof(struct load_command)))
		{
			data->exe = (to_swap(header->filetype, data) == MH_EXECUTE) ?
			0x100000000 : 0;
			data->obj = (to_swap(header->filetype, data) == MH_OBJECT) ? 1 : 0;
			lc = (void*)(header + 1);
			search_t_sec_64(data, lc, to_swap(header->ncmds, data));
			if (!data->error && data->sec)
				print_64(data);
		}
	}
}

void	parse_mach_o_32(t_data *data, uint32_t magic)
{
	struct mach_header		*header;
	struct load_command		*lc;

	data->swap = (magic == MH_CIGAM) ? 1 : 0;
	if (offset_check(data, sizeof(struct mach_header)))
	{
		header = (struct mach_header*)(data->ptr + data->offset);
		if (offset_check(data, sizeof(struct mach_header) +
			sizeof(struct load_command)))
		{
			data->exe = (to_swap(header->filetype, data) == MH_EXECUTE) ?
			0x1000 : 0;
			data->obj = (to_swap(header->filetype, data) == MH_OBJECT) ? 1 : 0;
			lc = (void*)(header + 1);
			search_t_sec_32(data, lc, to_swap(header->ncmds, data));
			if (!data->error && data->sec)
				print_32(data);
		}
	}
}

void	parse_lib(t_data *data)
{
	uint32_t	n_objs;
	uint32_t	i;
	uint32_t	filesize;
	size_t		len;

	n_objs = 0;
	i = 0;
	filesize = 0;
	len = 0;
	if (!data->error && !(filesize = get_filesize(data)))
		ft_putendl_fd("error parse_lib filesize", STDERR_FILENO);
	if (!data->error && offset_check(data, 2) && (len = filename_lenght(data)))
		data->offset += 60 + len;
	if (!data->error && offset_check(data, sizeof(uint32_t)))
		n_objs = *(uint32_t*)(data->ptr + data->offset) / sizeof(struct ranlib);
	data->offset += filesize - len;
	ft_putstr("Archive : ");
	ft_putendl(data->filename);
	if (!data->error && n_objs)
		while (i++ < n_objs && !data->error)
			lib_process(data);
	else if (!data->error)
		while ((len = filename_lenght(data)))
			lib_process(data);
}

void	parse_lib_64(t_data *data)
{
	uint32_t	n_objs;
	uint32_t	i;
	uint32_t	filesize;
	size_t		len;

	n_objs = 0;
	i = 0;
	filesize = 0;
	len = 0;
	if (!data->error && !(filesize = get_filesize(data)))
		ft_putendl_fd("error parse_lib filesize", STDERR_FILENO);
	if (!data->error && offset_check(data, 2) && (len = filename_lenght(data)))
		data->offset += 60 + len;
	if (!data->error && offset_check(data, sizeof(uint64_t)))
	{
		n_objs = *(uint64_t*)(data->ptr + data->offset) /
			sizeof(struct ranlib_64);
	}
	data->offset += filesize - len;
	if (!data->error && n_objs)
		while (i++ < n_objs && !data->error)
			lib_process(data);
	else if (!data->error)
		while ((len = filename_lenght(data)))
			lib_process(data);
}

void	parse_fat(t_data *data, uint32_t magic)
{
	struct fat_header	*f_header;
	struct fat_arch		*fa;

	data->swap = (magic == FAT_CIGAM) ? 1 : 0;
	data->fat = 1;
	if (sizeof(struct fat_header) <= data->filesize)
	{
		f_header = (struct fat_header*)data->ptr;
		if ((sizeof(struct fat_header) + sizeof(struct fat_arch))
				<= data->filesize)
		{
			fa = (void*)(f_header + 1);
			data->offset = to_swap(fa->offset, data);
			if (search_x86_64(data, fa, f_header->nfat_arch))
				ot_process(data);
			else
				fat_process(f_header, data);
		}
	}
}
