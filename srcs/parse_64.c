/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:42:52 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/30 13:07:23 by dgameiro         ###   ########.fr       */
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

void	sort_symtab_64(void *ptr, struct symtab_command *sc)
{
	uint32_t i;
	t_symbol_64 **table;

	if ((table = alloc_symbol_64(sc->nsyms)))
	{
		while (i < sc->nsyms)
		{
			if(tab[i].n_sect)
				print_type(ptr, tab[i].n_sect);
			printf("%u ",  tab[i].n_desc);
			printf("%llu ", tab[i].n_value);
			printf("%s\n", str + tab[i].n_un.n_strx);
			i++;
		}
	}
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
	return (table);
}
