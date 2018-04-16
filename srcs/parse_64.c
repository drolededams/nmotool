/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:42:52 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/16 19:58:54 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		parse_mach_o_64(t_data *data, uint32_t magic)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	char					**sectstr;

	data->swap = (magic == MH_CIGAM_64) ? 1 : 0;
	if (offset_check(data, sizeof(struct mach_header_64)))
	{
		header = (struct mach_header_64*)(data->ptr + data->offset);
		if (offset_check(data, sizeof(struct mach_header_64) +
			sizeof(struct load_command)))
		{
			lc = (void*)(header + 1);
			sectstr = get_sectnames_64(data, lc, to_swap(header->ncmds, data));
			lc = search_symtab(to_swap(header->ncmds, data), lc, data,
					MOD_SIZE_64);
			if (!data->error && to_swap(lc->cmd, data) == LC_SYMTAB && sectstr)
				get_symtab_64(data, (struct symtab_command*)lc, sectstr);
		}
	}
}

void		parse_mach_o_32(t_data *data, uint32_t magic)
{
	struct mach_header		*header;
	struct load_command		*lc;
	char					**sectstr;

	data->is_64 = 0; //utile ?
	data->swap = (magic == MH_CIGAM) ? 1 : 0;
	if (offset_check(data, sizeof(struct mach_header)))
	{
		header = (struct mach_header*)(data->ptr + data->offset);
		if (offset_check(data, sizeof(struct mach_header) +
			sizeof(struct load_command)))
		{
			lc = (void*)(header + 1);
			sectstr = get_sectnames_32(lc, to_swap(header->ncmds, data), data);
			lc = search_symtab(to_swap(header->ncmds, data), lc, data,
					MOD_SIZE);
			if (!data->error && to_swap(lc->cmd, data) == LC_SYMTAB && sectstr)
				get_symtab_32(data, (struct symtab_command*)lc, sectstr);
		}
	}
}

struct load_command	*search_symtab(uint32_t ncmds, struct load_command *lc,
	t_data *data, uint32_t modsize)
{
	uint32_t	i;
	uint32_t	offset;

	if (modsize == MOD_SIZE_64)
		offset = sizeof(struct mach_header_64) + sizeof(struct load_command);
	else
		offset = sizeof(struct mach_header) + sizeof(struct load_command);
	i = 0;
	while (i++ < to_swap(ncmds, data) && !data->error &&
			to_swap(lc->cmd, data) != LC_SYMTAB)
	{
		if ((to_swap(lc->cmdsize, data) % modsize) != 0)
			data->error = 2;
		if (!data->error && offset_check(data, sizeof(struct load_command) +
					to_swap(lc->cmdsize, data)))
		{
			offset += to_swap(lc->cmdsize, data);
			lc = (void*)lc + to_swap(lc->cmdsize, data);
		}
	}
	return (lc);
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
	filesize = 0;
	len = 0;//init car check avant data error
	if(!data->error && !(filesize = get_filesize(data)))
		ft_putendl_fd("error parse_lib filesize", STDERR_FILENO);
	if (!data->error && offset_check(data, 2) && (len = filename_lenght(data)))
		data->offset += 60 + len;
	if (!data->error && offset_check(data, sizeof(uint32_t)))//quittage a faire
	{
		n_objs = *(uint32_t*)(data->ptr + data->offset) / sizeof(struct ranlib);
	}
	data->offset += filesize - len;
	if (!data->error && n_objs)
	{
		while (i < n_objs && !data->error)
		{
			if ((len = filename_lenght(data)))
			{
				if (offset_check(data, 60))
				{
					if(!(filesize = get_filesize(data)))
						ft_putendl_fd("error parse_lib filesize", STDERR_FILENO);
				}
				else
					ft_putendl_fd("error parse_lib offset_check", STDERR_FILENO);
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
					ft_putendl_fd("error parse_lib offset_check", STDERR_FILENO);
			}
			i++;
		}
	}
	else if (!data->error)
	{
		while ((len = filename_lenght(data)))
		{
			if (offset_check(data, 60))
			{
				if(!(filesize = get_filesize(data)))
					ft_putendl_fd("error parse_lib filesize", STDERR_FILENO);
			}
			else
				ft_putendl_fd("error parse_lib offset_check", STDERR_FILENO);
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
				ft_putendl_fd("error parse_lib offset_check", STDERR_FILENO);
		}
	}
}

void	parse_lib_64(t_data *data)
{
	uint32_t	n_objs;
	uint32_t	i;
	uint32_t	filesize;
	size_t		len;
	char		*filename;

	n_objs = 0;
	i = 0;
	filesize = 0;
	len = 0;//init car check avant data error
	if(!data->error && !(filesize = get_filesize(data)))
		ft_putendl_fd("error parse_lib filesize", STDERR_FILENO);
	if (!data->error && offset_check(data, 2) && (len = filename_lenght(data)))
		data->offset += 60 + len;
	if (!data->error && offset_check(data, sizeof(uint64_t)))
	{
		n_objs = *(uint64_t*)(data->ptr + data->offset) / sizeof(struct ranlib_64);
	}
	data->offset += filesize - len;
	if (!data->error && n_objs)
	{
		while (i < n_objs && !data->error)
		{
			if ((len = filename_lenght(data)))
			{
				if (offset_check(data, 60))
				{
					if(!(filesize = get_filesize(data)))
						ft_putendl_fd("error parse_lib filesize", STDERR_FILENO);
				}
				else
					ft_putendl_fd("error parse_lib offset_check", STDERR_FILENO);
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
					ft_putendl_fd("error parse_lib offset_check", STDERR_FILENO);
			}
			//else
			//	ft_putendl("error parse_lib filename_lenght");
			//	marche sans else mais pourquoi ? dangerueux ? 
			i++;
		}
	}
	else if (!data->error)
	{
		while ((len = filename_lenght(data)))
		{
			if (offset_check(data, 60))
			{
				if(!(filesize = get_filesize(data)))
					ft_putendl_fd("error parse_lib filesize", STDERR_FILENO);
			}
			else
				ft_putendl_fd("error parse_lib offset_check", STDERR_FILENO);
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
				ft_putendl_fd("error parse_lib offset_check", STDERR_FILENO);
		}
	}
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
