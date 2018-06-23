/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:18:45 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/23 15:24:36 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

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

void	free_sectnames(char **sectnames)
{
	if (sectnames)
		ft_memdel((void**)&sectnames);
}

void	free_stab(t_symbol_64 **stab)
{
	int i;

	i = 0;
	if (stab)
	{
		while (stab[i])
		{
			ft_memdel((void**)&stab[i]);
			i++;
		}
		ft_memdel((void**)&stab);
	}
}
