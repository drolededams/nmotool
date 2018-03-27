/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:28:59 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/27 14:28:19 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	open_mmap(char *file)
{
	int			fd;
	struct stat	buf;
	void		*ptr;

	if ((fd = open(file, O_RDONLY)) < 0)
		error_file("Fail to open:", file, fd);
	else if (fstat(fd, &buf) == -1)
		error_file("fstat fail on", file, fd);
	else if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		error_file("mmap fail on", file, fd);
	else
	{
		nm_process(ptr);
		if (munmap(ptr, buf.st_size) == -1)
			error_file("munmap fail on", file, fd);
	}
}
