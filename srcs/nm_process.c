/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:00:12 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/05 17:16:46 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	nm_process(void *ptr, size_t filesize)
{
	mach_o_process(ptr, filesize);
}

void	mach_o_process(void *ptr, size_t filesize)
{
	uint32_t magic;

	magic = *(uint32_t*)ptr;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		parse_mach_o_64(ptr, filesize);
	//else
	//	parse_mach_o(ptr);
}
