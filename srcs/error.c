/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:55:30 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/05 16:35:34 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	error_file(char *str, char*file, int fd)
{
	ft_putstr(str);
	ft_putchar(' ');
	ft_putendl(file);
	if (fd >= 0)
		close(fd);
}

void	error_i_file(char*file, int fd)
{
	ft_putstr("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ");
	ft_putstr(file);
	ft_putendl(": No such file or directory.");
	if (fd >= 0)
		close(fd);
}
