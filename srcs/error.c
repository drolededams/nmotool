/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:55:30 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/12 17:55:17 by dgameiro         ###   ########.fr       */
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
	return (3);
}

uint32_t		error_i_file(t_data *data, int fd)
{
	ft_putstr("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ");
	ft_putstr(data->filename);
	ft_putendl(": No such file or directory.");
	if (fd >= 0)
		close(fd);
	return (3);
}

uint32_t		error_directory(t_data *data, int fd)
{
	ft_putstr("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ");
	ft_putstr(data->filename);
	ft_putendl(": Is a directory.");
	if (fd >= 0)
		close(fd);
	return (3);
}

int		put_error(t_data *data)
{
	ft_putstr("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ");
	ft_putstr(data->filename);
	if (data->error == 1)
		ft_putendl(" truncated or malformed object (load command 2 fileoff field plus filesize field in LC_SEGMENT_64 extends past the end of the file)");
	else if (data->error == 2)
		ft_putendl(" truncated or malformed object (load command 0 cmdsize not a multiple of 8)");
	else if (data->error == 4)
		ft_putendl(" The file was not recognized as a valid object file");
	ft_putchar('\n');
	return (1);
}
