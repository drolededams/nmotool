/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:42:52 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/29 17:36:31 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	parse_mach_o_64(void *ptr)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	uint32_t						i;

	i = 0;
	header = (struct mach_header_64*)ptr;
	lc = (void*)(header + 1);
	while (i++ < header->ncmds && lc->cmd != LC_SYMTAB)
		lc = (void*)lc + lc->cmdsize;
	if (lc->cmd == LC_SYMTAB)
		sort_symtab_64(ptr, (struct symtab_command*)lc);
	else
		ft_putendl("NO SYMTAB FOUND"); //to delete
}
