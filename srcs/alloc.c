/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:13:53 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/16 18:11:28 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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
