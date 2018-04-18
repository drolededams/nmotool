/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 13:54:47 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/18 15:41:54 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

unsigned long	to_swap(unsigned long value, t_data *data)
{
	if (data->swap)
		return (swap_bit(value));
	return (value);
}

unsigned long	swap_bit(unsigned long value)
{
	return (((value << 24) & 0xFF000000) | ((value << 8) & 0xFF0000) |
	((value >> 8) & 0xFF00) | ((value >> 24) & 0xFF));
}

uint64_t		to_swap_64(uint64_t value, t_data *data)
{
	if (data->swap)
		return (swap_bit_64(value));
	return (value);
}

uint64_t		swap_bit_64(uint64_t value)
{
	return (((value << 56) & 0xFF00000000000000) |
	((value << 40) & 0xFF000000000000) |
	((value << 24) & 0xFF0000000000) |
	((value << 8) & 0xFF00000000) |
	((value >> 8) & 0xFF000000) |
	((value >> 24) & 0xFF0000) |
	((value >> 40) & 0xFF00) |
	((value >> 56) & 0xFF));
}
