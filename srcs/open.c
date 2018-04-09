/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:28:59 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/09 15:57:53 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	open_mmap(char *file, int multi, t_data *data)
{
	int			fd;
	struct stat	buf;

	data->filename = ft_strdup(file);
	data->swap = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		error_i_file(file, fd); //a voir directory etc..
	else if (fstat(fd, &buf) == -1)
		error_file("fstat fail on", file, fd);
	else if ((data->ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		error_file("mmap fail on", file, fd);
	else
	{
		data->filesize = buf.st_size;
		if (multi)
		{
			ft_putchar('\n');
			ft_putstr(file);
			ft_putstr(":\n");
		}
		nm_process(data);
		if (munmap(data->ptr, buf.st_size) == -1)// a voir
			error_file("munmap fail on", file, fd);
	}
}
