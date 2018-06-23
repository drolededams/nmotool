/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 13:51:11 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/23 15:48:23 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

void	static_lib_process(t_data *data)
{
	if (header_lib_check(data))
	{
		data->libstatic = 1;
		if ((offset_check(data, 60 + ft_strlen(SYMDEF_64)) &&
ft_strnequ(data->ptr + data->offset + 60, SYMDEF_64, ft_strlen(SYMDEF_64))))
			parse_lib_64(data);
		else if (offset_check(data, 60 + ft_strlen(SYMDEF)) &&
ft_strnequ(data->ptr + data->offset + 60, SYMDEF, ft_strlen(SYMDEF)))
			parse_lib(data);
	}
	else
		ft_putendl_fd("Bad header lib", STDERR_FILENO);
}

int		header_lib_check(t_data *data)
{
	if (data->filesize >= data->offset + 60)
		return (ft_strnequ(data->ptr + data->offset + 58, "`\n", 2));
	return (0);
}

size_t	filename_lenght(t_data *data)
{
	char	*str;
	size_t	len;

	if (data->filesize > data->offset + 2 &&
ft_strnequ(data->ptr + data->offset, "#1/", 3))
	{
		str = ft_strnew(13);
		ft_strncpy(str, data->ptr + data->offset + 3, 13);
		len = (size_t)ft_atoi(str);
		ft_memdel((void**)&str);
		return (len);
	}
	return (0);
}

size_t	get_filesize(t_data *data)
{
	char	*str;
	size_t	len;

	len = 0;
	str = ft_strnew(8);
	if (offset_check(data, 56))
	{
		ft_strncpy(str, data->ptr + data->offset + 48, 8);
		len = (size_t)ft_atoi(str);
	}
	ft_memdel((void**)&str);
	return (len);
}

int		is_static(t_data *data)
{
	if ((offset_check(data, 8)) && ft_strnequ(data->ptr + data->offset,
"!<arch>\n", 8))
	{
		data->offset += 8;
		return (1);
	}
	return (0);
}
