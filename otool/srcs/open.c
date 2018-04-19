/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:28:59 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/19 18:52:21 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

uint32_t		open_mmap(char *file, int multi, t_data *data)
{
	int			fd;
	struct stat	buf;

	init_data(data, multi, file);
	if ((fd = open(file, O_RDONLY)) < 0)
		return (error_i_file(data, fd));
	else if (fstat(fd, &buf) == -1)
		return (error_file("fstat fail on", data, fd));
	else if (S_ISDIR(buf.st_mode))
		return (error_directory(data, fd));
	else if ((data->ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (error_file("mmap fail on", data, fd));
	else
	{
		data->filesize = buf.st_size;
		ot_process(data);
		close(fd);
		if (munmap(data->ptr, buf.st_size) == -1)
			data->error = error_file("munmap fail on", data, fd);
		return (data->error);
	}
}

void			init_data(t_data *data, int multi, char *file)
{
	data->filename = ft_strdup(file);
	data->sec = NULL;
	data->offset = 0;
	data->swap = 0;
	data->error = 0;
	data->fat = 0;
	data->nfat = 0;
	data->multi = multi;
	data->libstatic = 0;
	data->nsects = 0;
	data->obj = 0;
	data->exe = 0;
}
