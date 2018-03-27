/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:06:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/27 17:19:46 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"


void	sort_symtab_64(void *ptr, struct symtab_command *sc)
{
	uint32_t i;
	char *str;
	struct nlist_64  *tab;

	tab = ptr + sc->symoff;
	str = ptr + sc->stroff;
	i = 0;
	while (i < sc->nsyms)
	{
		printf("%u ", tab[i].n_type & N_TYPE);
		if(tab[i].n_sect)
			print_type(ptr, tab[i].n_sect);
		printf("%u ", tab[i].n_desc);
		printf("%llu ", tab[i].n_value);
		printf("%s\n", str + tab[i].n_un.n_strx);
		i++;
	}
}

void	print_type(void *ptr, uint8_t sect)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct segment_command_64	*sc;
	uint32_t					i;

	i = 0;
	header = (struct mach_header_64*)ptr;
	sect = 1;
	lc = (void*)(header + 1);
	while (i < header->ncmds && lc->cmd != LC_SEGMENT_64)
		lc = (void*)lc + lc->cmdsize;
	if (lc->cmd == LC_SEGMENT_64)
	{
		sc = (struct segment_command_64*)lc;
		printf(" s= %s ", sc->segname);
	}


}
