/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:00:12 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/29 14:26:58 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	nm_process(void *ptr)
{
	mach_o_process(ptr);
}

void	mach_o_process(void *ptr)
{
	uint32_t magic;

	magic = *(uint32_t*)ptr;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		parse_mach_o_64(ptr);
	//else
	//	parse_mach_o(ptr);
}
