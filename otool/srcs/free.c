/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:18:45 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/19 11:06:28 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	free_data(t_data *data)
{
	if (data)
	{
		free_filename(data);
		ft_memdel((void**)&data);
	}
}

void	free_filename(t_data *data)
{
	if (data->filename)
		ft_memdel((void**)&data->filename);
}
