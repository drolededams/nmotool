/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:42:52 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/13 13:37:15 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		parse_mach_o_64(t_data *data)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	uint32_t				i;
	uint32_t				total_offset;
	char					**sectnames;

	i = 0;
	if (offset_check(data, sizeof(struct mach_header_64)))
	{
		total_offset = sizeof(struct mach_header_64);
		header = (struct mach_header_64*)(data->ptr + data->offset);
		if (offset_check(data, total_offset + sizeof(struct load_command)))
		{
			total_offset += sizeof(struct load_command);
			lc = (void*)(header + 1);
			sectnames = get_sectnames_64(data, lc, header->ncmds);
			while (i++ < header->ncmds && !data->error && lc->cmd != LC_SYMTAB)
			{
				if (lc->cmdsize % 8 != 0)
					data->error = 2;
				if (!data->error && offset_check(data, total_offset + sizeof(struct load_command) + lc->cmdsize))
				{
					total_offset += lc->cmdsize;
					lc = (void*)lc + lc->cmdsize;
				}
			}
			if (!data->error && lc->cmd == LC_SYMTAB)
				get_symtab_64(data, (struct symtab_command*)lc, sectnames);
		}
	}
}

void		parse_mach_o_32(t_data *data)
{
	struct mach_header	*header;
	struct load_command		*lc;
	uint32_t				i;
	char					**sectnames;
	uint32_t				magic;

	i = 0;
	magic = *(uint32_t*)(data->ptr + data->offset);
	data->swap = 0;
	data->is_64 = 0;
	if (magic == MH_CIGAM)
		data->swap = 1;
	header = (struct mach_header*)(data->ptr + data->offset);
	lc = (void*)(header + 1);
	sectnames = get_sectnames_32(lc, to_swap(header->ncmds, data), data);
	while (i++ < to_swap(header->ncmds, data) && to_swap(lc->cmd, data) != LC_SYMTAB)
	{
		if (to_swap(lc->cmdsize, data) % 4 != 0)//cas a gerer par un break ou autre + propre
			ft_putendl("not a multiple of 8");
		lc = (void*)lc + to_swap(lc->cmdsize, data);
	}
	if (to_swap(lc->cmd, data) == LC_SYMTAB)
	{
		get_symtab_32(data, (struct symtab_command*)lc, sectnames);
	}
}

void	parse_lib(t_data *data)
{
	uint32_t	n_objs;
	uint32_t	i;
	uint32_t	filesize;
	size_t		len;
	char		*filename;

	n_objs = 0;
	i = 0;
	if(!(filesize = get_filesize(data)))
		ft_putendl("error parse_lib filesize");
	if ((len = filename_lenght(data)))
		data->offset += 60 + len;
	if (offset_check(data, sizeof(uint32_t)))
	{
		n_objs = *(uint32_t*)(data->ptr + data->offset) / sizeof(struct ranlib);
	}
	if (offset_check(data, filesize - len))
		data->offset += filesize - len;
	if (n_objs)
	{
		while (i < n_objs)
		{
			if ((len = filename_lenght(data)))
			{
				if (offset_check(data, 60))
				{
					if(!(filesize = get_filesize(data)))
						ft_putendl("error parse_lib filesize");
				}
				else
					ft_putendl("error parse_lib offset_check");
				data->offset += 60;
				if (offset_check(data, len))
				{
					filename = ft_strnew(len);
					ft_strncpy(filename, data->ptr + data->offset, len);
					ft_putchar('\n');
					ft_putstr(data->filename);
					ft_putchar('(');
					ft_putstr(filename);
					ft_putendl("):");
					ft_memdel((void**)&filename);
					data->offset += len;
					nm_process(data);
					data->offset += filesize - len;
				}
				else
					ft_putendl("error parse_lib offset_check");
			}
			//else
			//	ft_putendl("error parse_lib filename_lenght");
			//	marche sans else mais pourquoi ? dangerueux ? 
			i++;
		}
	}
	else
	{
		while ((len = filename_lenght(data)))
		{
			if (offset_check(data, 60))
			{
				if(!(filesize = get_filesize(data)))
					ft_putendl("error parse_lib filesize");
			}
			else
				ft_putendl("error parse_lib offset_check");
			data->offset += 60;
			if (offset_check(data, len))
			{
				filename = ft_strnew(len);
				ft_strncpy(filename, data->ptr + data->offset, len);
				ft_putchar('\n');
				ft_putstr(data->filename);
				ft_putchar('(');
				ft_putstr(filename);
				ft_putendl("):");
				ft_memdel((void**)&filename);
				data->offset += len;
				nm_process(data);
				data->offset += filesize - len;
			}
			else
				ft_putendl("error parse_lib offset_check");
		}
	}
}

void	parse_lib_64(t_data *data)
{
	uint64_t	n_objs;
	uint64_t	i;
	size_t		len;

	n_objs = 0;
	i = 0;
	if ((len = filename_lenght(data)))
		data->offset += 60 + len;
	if (offset_check(data, sizeof(uint64_t)))
	{
		n_objs = *(uint64_t*)(data->ptr + data->offset) / sizeof(struct ranlib);
		data->offset += *(uint64_t*)(data->ptr + data->offset);
	}
	if (offset_check(data, sizeof(uint64_t)))
		data->offset += *(uint64_t*)(data->ptr + data->offset);
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
	data->fat = 1;
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
				nm_process(data);
			}
			else
				fat_process(header, data);
		}
	}
}
