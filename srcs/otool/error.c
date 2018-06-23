/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:55:30 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/23 15:47:53 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

uint32_t		error_file(char *str, t_data *data, int fd)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	ft_putendl_fd(data->filename, STDERR_FILENO);
	if (fd >= 0)
		close(fd);
	if (ft_strequ("munmap fail on", str))
		return (1 << 2);
	return (3);
}

uint32_t		error_i_file(t_data *data, int fd)
{
	ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/\
XcodeDefault.xctoolchain/usr/bin/nm: ", STDERR_FILENO);
	ft_putstr_fd(data->filename, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory.", STDERR_FILENO);
	if (fd >= 0)
		close(fd);
	return (3);
}

uint32_t		error_directory(t_data *data, int fd)
{
	ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/\
XcodeDefault.xctoolchain/usr/bin/nm: ", STDERR_FILENO);
	ft_putstr_fd(data->filename, STDERR_FILENO);
	ft_putendl_fd(": Is a directory.", STDERR_FILENO);
	if (fd >= 0)
		close(fd);
	return (3);
}

int				put_error(t_data *data)
{
	if (data->error == 3)
		return (1);
	if (data->error == 4)
	{
		ft_putstr(data->filename);
		ft_putendl(": is not an object file");
		return (0);
	}
	ft_putstr_fd(data->filename, STDERR_FILENO);
	if (data->error == 1)
		ft_putendl_fd(" truncated or malformed object \
(past the end of the file)", STDERR_FILENO);
	else if (data->error == 2)
		ft_putendl_fd(" truncated or malformed object \
(not a multiple of 8)", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}
