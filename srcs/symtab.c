/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:06:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/05 18:13:26 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	test_64(void *ptr, struct symtab_command *sc)
{
	uint32_t i;
	uint32_t j;
	//char *str;
	//struct nlist_64  *tab;
	struct section_64			*se;
	struct load_command		*lc;
	struct mach_header_64		*header;
	//struct segment_command_64 *sct;
/*
	tab = ptr + sc->symoff;
	str = ptr + sc->stroff;
	i = 0;
	while (i < sc->nsyms)
	{
		printf("ntype = %u ", tab[i].n_type & N_TYPE);
		printf("sect = %u ", tab[i].n_sect);
		if(tab[i].n_sect)
			print_type(ptr, tab[i].n_sect);
		printf("%u ",  tab[i].n_desc);
		printf("%llu ", tab[i].n_value);
		printf("%s\n", str + tab[i].n_un.n_strx);
		i++;
	}
	i = 0;
	header = (struct mach_header_64*)ptr;
	lc = (void*)(header + 1);
	printf("ncmds = %u\n", header->ncmds);
	while (i++ < header->ncmds && lc->cmd != LC_SEGMENT_64)
		lc = (void*)lc + lc->cmdsize;
	i = 0;
	if (lc->cmd == LC_SEGMENT_64)
	{
		sct = (struct segment_command_64*)lc;
		printf("seggggname = %s\n", sct->segname);
		printf("cmd = %u\n", sct->cmd);
		printf("cmd f = %u\n", LC_SEGMENT_64);
		printf(" sizeof segment_command_64= %lu\n", sizeof(struct segment_command_64));
		printf(" size= %u\n", sct->cmdsize);
		printf("nsects = %u\n",sct->nsects);
		while (i < ((struct segment_command_64*)lc)->nsects)
		{
			se = (struct section_64*)((void*)sct + sizeof(struct segment_command_64) + (i - 1) * sizeof(struct section_64));
			printf("sectname = %s\n", se->sectname);
			i++;
		}
	}
	*/
	sc = NULL;
	i = 0;
	header = (struct mach_header_64*)ptr;
	lc = (void*)(header + 1);
			printf("\n\n\nSEGMENTS\n\n");
	while (i++ < header->ncmds)
	{
		if(lc->cmd == LC_SEGMENT_64)
		{
			printf("segname of the win %u  = %s\n", i - 1 , ((struct segment_command_64*)lc)->segname);
			printf("add  = %p\n",  ((struct segment_command_64*)lc));
			printf("size  = %u\n",  ((struct segment_command_64*)lc)->cmdsize);
			printf("nsects  = %u\n",  ((struct segment_command_64*)lc)->nsects);
			printf("**filesize**  = %llu\n",  ((struct segment_command_64*)lc)->filesize);
			printf("**fileoff**  = %llu\n",  ((struct segment_command_64*)lc)->fileoff);
			printf("nsects  = %u\n",  ((struct segment_command_64*)lc)->nsects);
			j = 0;
			while (j++ < ((struct segment_command_64*)lc)->nsects)
			{
				se = (struct section_64*)((void*)lc + sizeof(struct segment_command_64) + (j - 1) * sizeof(struct section_64));
				printf("segame = %s\n", se->segname);
				printf("sectname = %s\n", se->sectname);
				printf("add sect = %p\n", se);
				printf("offset sect = %u\n", se->offset);
			}
		}
		else if (lc->cmd == LC_SYMTAB)
		{
			printf("segname of the win %u LC_SYMTAB\n", i - 1);
			printf("add  = %p\n",  ((struct symtab_command*)lc));
			printf("size  = %u\n",  ((struct symtab_command*)lc)->cmdsize);
			//printf("add_str  = %p\n",  str);
			//printf("add_tab  = %p\n",  tab);
		}
		else
		{
			printf("segname of the win %u \n", i - 1);
			printf("add  = %p\n",  lc);
			printf("size  = %u\n",  lc->cmdsize);
		}
			printf("\n=====================\n\n\n\n");
		lc = (void*)lc + lc->cmdsize;
	}
}

void	print_type(void *ptr, uint8_t sect)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct section_64			*se;
	uint32_t					i;

	i = 0;
	header = (struct mach_header_64*)ptr;
	lc = (void*)(header + 1);
	while (i < header->ncmds && lc->cmd != LC_SEGMENT_64)
		lc = (void*)lc + lc->cmdsize;
	if (lc->cmd == LC_SEGMENT_64)
	{
		se = (struct section_64*)((void*)lc + lc->cmdsize + (sect - 1) * sizeof(struct section_64));
		printf(" sectname= %s ", se->sectname);
		printf(" segname= %s ", se->segname);
		printf(" size= %llu ", se->size);
		printf(" sizeof= %lu ", sizeof(struct section_64));
		printf(" flags= %u ", se->flags & 127);
	}
}

void	get_symtab_64(void *ptr, struct symtab_command *sc, char **sectnames)
{
	uint32_t i;
	t_symbol_64 **stab;
	char *str;
	struct nlist_64  *tab;

	tab = ptr + sc->symoff; //verifier offset
	str = ptr + sc->stroff;//verifier iffset
	if ((stab = alloc_symbol_64(sc->nsyms)))
	{
		i = 0;
		while (i < sc->nsyms)
		{
			stab[i]->value = tab[i].n_value;
			stab[i]->type = get_type(tab[i], sectnames);
			stab[i]->name = str + tab[i].n_un.n_strx;
			i++;
		}
		quicksort_64(stab, 1, sc->nsyms);
		print_st64(stab);
	}
	else
		ft_putendl("Allocation failed");
}
