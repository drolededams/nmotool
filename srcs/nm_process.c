/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:00:12 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/11 19:13:58 by dgameiro         ###   ########.fr       */
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

void	static_lib_process(t_data *data)
{
	if (header_lib_check(data))
	{
		if (ft_strnequ(data->ptr + data->offset + 60, SYMDEF_64, ft_strlen(SYMDEF_64)))
			parse_lib_64(data);
		else if (ft_strnequ(data->ptr + data->offset + 60, SYMDEF, ft_strlen(SYMDEF)))
			parse_lib(data);
	}
	else
		ft_putendl("Bad header lib");
}

int		header_lib_check(t_data *data)
{
	if (data->filesize >= data->offset + 60)
		return (ft_strnequ(data->ptr + data->offset + 58, "`\n", 2));
	return (0);
}

size_t		filename_lenght(t_data *data)
{
	char	*str;
	size_t	len;

	if (ft_strnequ(data->ptr + data->offset, "#1/", 3))
	{
		str = ft_strnew(13);
		ft_strncpy(str, data->ptr + data->offset + 3, 13);
		len = (size_t)ft_atoi(str);
		ft_memdel((void**)&str);
		return (len);
	}
	return (0);
}

size_t		get_filesize(t_data *data)
{
	char	*str;
	size_t	len;

	len = 0;
	str = ft_strnew(8);
	ft_strncpy(str, data->ptr + data->offset + 48, 8);
	len = (size_t)ft_atoi(str);
	ft_memdel((void**)&str);
	return (len);
}

int		offset_check(t_data *data, size_t size)
{
	if (data->offset + size < data->filesize)
		return (1);
	return (0);
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
				if (offset_check(data, filesize - len))
					data->offset += filesize - len;
			}
			else
				ft_putendl("error parse_lib offset_check");
		}
		//else
		//	ft_putendl("error parse_lib filename_lenght");
		i++;
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

int		is_static(t_data *data)
{
	if (data->filesize >= 8 + data->offset && ft_strnequ(data->ptr + data->offset, "!<arch>\n", 8))
	{
		data->offset += 8;
		return (1);
	}
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
