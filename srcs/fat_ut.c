/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_ut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:36:17 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/17 16:37:32 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		search_x86_64(t_data *data, struct fat_arch *fa, uint32_t nfat_arch)
{
	size_t			total_offset;
	unsigned long	i;

	total_offset = sizeof(struct fat_header);
	i = 0;
	while (i < to_swap(nfat_arch, data) &&
			(cpu_type_t)(to_swap(fa->cputype, data)) != CPU_TYPE_X86_64)
	{
		if (total_offset + sizeof(struct fat_arch) <= data->filesize)
		{
			fa = (void*)fa + sizeof(struct fat_arch);
			total_offset += sizeof(struct fat_arch);
		}
		i++;
	}
	if (to_swap(fa->cputype, data) == CPU_TYPE_X86_64)
	{
		data->offset = to_swap(fa->offset, data);
		return (1);
	}
	return (0);
}
