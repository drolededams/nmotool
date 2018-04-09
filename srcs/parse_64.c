/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:42:52 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/09 18:03:11 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		parse_mach_o_64(t_data *data)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	uint32_t				i;
	char					**sectnames;

	i = 0;
	header = (struct mach_header_64*)(data->ptr + data->offset);
	lc = (void*)(header + 1);
	sectnames = get_sectnames_64(lc, header->ncmds);
	while (i++ < header->ncmds && lc->cmd != LC_SYMTAB)
	{
		if (lc->cmdsize % 8 != 0)//cas a gerer par un break ou autre + propre
			ft_putendl("not a multiple of 8");
		lc = (void*)lc + lc->cmdsize;
	}
	if (lc->cmd == LC_SYMTAB)
	{
		get_symtab_64(data, (struct symtab_command*)lc, sectnames);
	}
}

void		parse_mach_o_32(t_data *data)
{
	struct mach_header	*header;
	struct load_command		*lc;
	uint32_t				i;
	char					**sectnames;
	uint32_t				magic;

	i = 0;
	magic = *(uint32_t*)(data->ptr + data->offset);
	data->swap = 0;
	if (magic == MH_CIGAM)
		data->swap = 1;
	header = (struct mach_header*)(data->ptr + data->offset);
	lc = (void*)(header + 1);
	sectnames = get_sectnames_32(lc, to_swap(header->ncmds, data), data);
	while (i++ < to_swap(header->ncmds, data) && to_swap(lc->cmd, data) != LC_SYMTAB)
	{
		if (to_swap(lc->cmdsize, data) % 4 != 0)//cas a gerer par un break ou autre + propre
			ft_putendl("not a multiple of 8");
		lc = (void*)lc + to_swap(lc->cmdsize, data);
	}
	if (to_swap(lc->cmd, data) == LC_SYMTAB)
	{
		get_symtab_32(data, (struct symtab_command*)lc, sectnames);
	}
}
