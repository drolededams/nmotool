/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:42:52 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/06 18:01:16 by dgameiro         ###   ########.fr       */
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
	header = (struct mach_header_64*)data->ptr;
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
