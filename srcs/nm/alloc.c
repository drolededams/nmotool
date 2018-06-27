/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:13:53 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/23 18:36:00 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

t_symbol_64	**alloc_symbol_64(uint32_t nsyms)
{
	t_symbol_64	**table;
	uint32_t	i;

	if (!(table = (t_symbol_64**)malloc(sizeof(t_symbol_64*) * (nsyms + 1))))
		return (NULL);
	i = 0;
	while (i < nsyms)
	{
		if (!(table[i] = (t_symbol_64*)malloc(sizeof(t_symbol_64))))
			return (NULL);
		i++;
	}
	table[i] = NULL;
	return (table);
}

int			offset_check_sec(t_data *data, uint32_t offset, size_t size)
{
	if (!offset_check(data, size))
		return (0);
	else if (!offset_check(data, offset))
		return (0);
	else if (SIZE_MAX - size < offset)
	{
		data->error = 1;
		return (0);
	}
	else if (!offset_check(data, size + offset))
		return (0);
	else
	{
		data->error = 0;
		return (1);
	}
}
