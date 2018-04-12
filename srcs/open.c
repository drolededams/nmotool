/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:28:59 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/12 16:51:39 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

uint32_t		open_mmap(char *file, int multi, t_data *data)
{
	int			fd;
	struct stat	buf;

	data->filename = ft_strdup(file);
	data->swap = 0;
	data->error = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return(error_i_file(data, fd)); //a voir directory etc..
	else if (fstat(fd, &buf) == -1)
		return (error_file("fstat fail on", data, fd));
	else if (buf.st_mode == S_IFDIR)
		return (error_directory(data, fd));
	else if ((data->ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (error_file("mmap fail on", data, fd));
	else
	{
		data->filesize = buf.st_size;
		if (multi)
		{
			ft_putchar('\n');
			ft_putstr(file);
			ft_putstr(":\n");
		}//sauf quand fat ??
		data->offset = 0;
		data->fat = 0;
		nm_process(data);
		close(fd);
		if (munmap(data->ptr, buf.st_size) == -1)// a voir
			data->error &= error_file("munmap fail on", data, fd);
		return (data->error);
	}
}
