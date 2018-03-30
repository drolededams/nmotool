/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:42:52 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/30 19:33:46 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		parse_mach_o_64(void *ptr)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	uint32_t				i;
	char					**sectnames;

	i = 0;
	//LC_DYSYMTAB
	header = (struct mach_header_64*)ptr;
	lc = (void*)(header + 1);
	sectnames = get_sectnames_64(lc, header->ncmds);
	while (i++ < header->ncmds && lc->cmd != LC_SYMTAB)
		lc = (void*)lc + lc->cmdsize;
	if (lc->cmd == LC_SYMTAB)
		test_64(ptr, (struct symtab_command*)lc);
	else
		ft_putendl("NO SYMTAB FOUND"); //to delete
}

char		**get_sectnames_64(struct load_command *lc, uint32_t ncmds)
{
	uint32_t			i;
	uint32_t			j;
	uint32_t			k;
	uint32_t			nsects;
	struct load_command	*cur;
	struct section_64	*section;
	char				**sectnames;

	i = 0;
	nsects = 0;
	cur = lc;
	while (i++ < ncmds)
	{
		if (cur->cmd == LC_SEGMENT_64)
			nsects += ((struct segment_command_64*)cur)->nsects;
		cur = (void*)cur + cur->cmdsize;
	}
	if ((sectnames = (char**)malloc(sizeof(char*) * nsects -1)) != NULL)
	{
		i = 0;
		while (i < ncmds)
		{
			if (lc->cmd == LC_SEGMENT_64)
			{
				j = 0;
				while (j++ < ((struct segment_command_64*)lc)->nsects)
				{
					section = (struct section_64*)((void*)lc + sizeof(struct segment_command_64) + (j - 1) * sizeof(struct section_64));
					sectnames[k] = section->sectname;
					k++;
				}
			}
			i++;
			lc = (void*)lc + lc->cmdsize;
		}
	}
	return (sectnames);
}

void	get_symtab_64(struct symtab_command *sc, char **sectnames)
{
	uint32_t i;
	t_symbol_64 **stab;

	if ((stab = alloc_symbol_64(sc->nsyms)))
	{
		i = 0;
		while (i < sc->nsyms)
		{
			stab[i]->value = tab[i].n_value;
			stab[i]->type = get_type(ptr, tab[i]);
			stab[i]->name = str + tab[i].n_un.nstrx;
			i++;
		}
		quicksort_64(stab, 1, sc->nsyms);
		print_st64
	}
	else
		ft_putendl("Allocation failed");
}

void	quicksort_64(t_symbol_64 **stab, uint32_t first, uint32_t last)
{
	if (first < last)
	{
		piv = split_64(stab, first, last, first - 1);
		quicksort_64(stab, first, piv - 1);
		quicksort_64(stab, piv + 1, last);
	}
}

uint32_t split_64(t_symbol_64 **stab, uint32_t first, uint32_t last, uint32_t piv)
{
	t_symbol_64 *swap;
	uint32_t i;
	uint32_t j;

	i = first - 1;
	j = first - 1;
	swap = stab[piv];
	stab[piv] = stab[last - 1];
	stab[last - 1] = swap;
	while (i < last - 1)
	{
		if (ft_strcmp(stab[i]->name[0], stab[last - 1]->name[0]) <= 0)
		{
			swap = stab[i];
			stab[i] = stab[j];
			stab[j] = swap;
			j++;
		}
		i++;
	}
	swap = stab[last - 1];
	stab[last - 1] = stab[j];
	stab[j] = swap;
	return (j + 1);
}

char	get_type(void *ptr, struct nlist_64 nl, char **sectnames)
{
	if ((nl.n_type & N_EXT) && (nl.n_type & N_TYPE) == N_UNDF)
		return ('C');
	if ((nl.n_type & N_TYPE) == N_UNDF)
		return ('U');
	if ((nl.n_type & N_TYPE) == N_ABS)
		return ('A');
	if ((nl.n_type & N_TYPE) == N_SECT)
		return (get_sect_64(nl.n_sect, sectnames));
	return (' ');
}

char	get_sect_64(uint8_t n_sect, char **sectnames)
{
	if (!(ft_strcmp(sectnames[n_sect], "__text"))//convention __lower ?
			return ('T');
	if (!(ft_strcmp(sectnames[n_sect], "__data"))
			return ('D');
	if (!(ft_strcmp(sectnames[n_sect], "__bss"))
			return ('B');
	if (!(ft_strcmp(sectnames[n_sect], "__picsymbol_stub"))
			return ('I');
	if (!(ft_strcmp(sectnames[n_sect], "__symbol_stub"))
			return ('I');
	return ('S');
}

t_symbol_64 **alloc_symbol_64(uint32_t nsyms)
{
	t_symbol_64	**table;
	uint32_t	i;

	if (!(table = (**t_symbol_64)malloc(sizeof(t_symbol_64*) * (nsyms + 1))))
		return (NULL);
	i = 0;
	while (i < nsyms)
	{
		if (!(table[i] = (*t_symbol_64)malloc(sizeof(t_symbol_64))))
			return (NULL);
		i++;
	}
	table[i] = NULL;
	return (table);
}
