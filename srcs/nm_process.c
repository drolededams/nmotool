/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:00:12 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/06 17:55:04 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	nm_process(t_data *data)
{
	//test_64(data->ptr);
	mach_o_process(data);
}

void	mach_o_process(t_data *data)
{
	uint32_t magic;

	magic = *(uint32_t*)data->ptr;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		parse_mach_o_64(data);
	//else
	//	parse_mach_o(ptr);
}
