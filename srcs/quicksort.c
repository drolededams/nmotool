/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:21:55 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/13 20:06:22 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	quicksort_64(t_symbol_64 **stab, uint32_t first, uint32_t last)
{
	uint32_t piv;

	if (first < last)
	{
		piv = split_64(stab, first, last, first - 1);
		quicksort_64(stab, first, piv - 1);
		quicksort_64(stab, piv + 1, last);
	}
}

uint32_t split_64(t_symbol_64 **stab, uint32_t first, uint32_t last, uint32_t piv)
{
	t_symbol_64 *swap;
	uint32_t i;
	uint32_t j;

	i = first - 1;
	j = first - 1;
	swap = stab[piv];
	stab[piv] = stab[last - 1];
	stab[last - 1] = swap;
	while (i < last - 1)
	{
		if (ft_strcmp(stab[i]->name, stab[last - 1]->name) < 0)
		{
			swap = stab[i];
			stab[i] = stab[j];
			stab[j] = swap;
			j++;
		}
		else if (ft_strcmp(stab[i]->name, stab[last - 1]->name) == 0 && stab[i]->value < stab[last - 1]->value)
		{
			swap = stab[i];
			stab[i] = stab[j];
			stab[j] = swap;
			j++;
		}
		i++;
	}
	swap = stab[last - 1];
	stab[last - 1] = stab[j];
	stab[j] = swap;
	return (j + 1);
}
