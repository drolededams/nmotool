/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:42:52 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/05 18:33:49 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		parse_mach_o_64(void *ptr, size_t filesize)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	uint32_t				i;
	char					**sectnames;

	i = 0;
	//LC_DYSYMTAB
	header = (struct mach_header_64*)ptr;
	lc = (void*)(header + 1);
	filesize = 0;
	sectnames = get_sectnames_64(lc, header->ncmds);
	while (i++ < header->ncmds && lc->cmd != LC_SYMTAB)
	{
		if (lc->cmdsize % 8 != 0)//cas a gerer par un break
			ft_putendl("not a multiple of 8");
		lc = (void*)lc + lc->cmdsize;
	}
	if (lc->cmd == LC_SYMTAB)
	{
		test_64(ptr, (struct symtab_command*)lc);
		//get_symtab_64(ptr, (struct symtab_command*)lc, sectnames);
	}
}
