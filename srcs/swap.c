/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 13:54:47 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/12 13:55:54 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

unsigned long	to_swap(unsigned long value, t_data *data)
{
	if(data->swap)
		return (swap_bit(value));
	return (value);
}

unsigned long	swap_bit(unsigned long value)
{
	return (((value << 24) & 0xFF000000) | ((value << 8) & 0xFF0000) | ((value >> 8) & 0xFF00) | ((value >> 24) & 0xFF));
}
