/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:55:30 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/12 15:35:40 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

uint32_t		error_file(char *str, t_data *data, int fd)
{
	ft_putstr(str);
	ft_putchar(' ');
	ft_putendl(data->filename);
	if (fd >= 0)
		close(fd);
	if (ft_strequ("munmap fail on", str))
		return (1 << 2);
	return (1);
}

uint32_t		error_i_file(t_data *data, int fd)
{
	ft_putstr("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ");
	ft_putstr(data->filename);
	ft_putendl(": No such file or directory.");
	if (fd >= 0)
		close(fd);
	return (1);
}

uint32_t		error_directory(t_data *data, int fd)
{
	ft_putstr("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ");
	ft_putstr(data->filename);
	ft_putendl(": Is a directory.");
	if (fd >= 0)
		close(fd);
	return (1);
}
