/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:06:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/06 18:26:35 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	test_64(void *ptr)
{
	uint32_t i;
	uint32_t j;
	struct section_64			*se;
	struct load_command		*lc;
	struct mach_header_64		*header;

	i = 0;
	header = (struct mach_header_64*)ptr;
	printf("magic == %u\n", header->magic);
	printf("magic hex == %s\n", value_to_str_64(header->magic, "0123456789abcdef"));
	printf("filetype == %u\n", header->filetype);
	printf("filetype hex == %s\n", value_to_str_64(header->filetype, "0123456789abcdef"));
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
			printf("cmd  = %u\n",  lc->cmd);
			printf("cmd hex  = %s\n",  value_to_str_64(lc->cmd, "0123456789abcdef"));
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

uint32_t symtab_lenght_64(struct nlist_64 *tab, struct symtab_command *sc)
{
	uint32_t length;
	uint32_t i;

	length = 0;
	i = 0;
	while (i < sc->nsyms)
	{
		if(!(tab[i].n_type & N_STAB))
			length++;
		i++;
	}
	return (length);
}

void	get_symtab_64(t_data *data, struct symtab_command *sc, char **sectnames)
{
	uint32_t i;
	uint32_t j;
	uint32_t length;
	t_symbol_64 **stab;
	char *str;
	struct nlist_64  *tab;

	tab = data->ptr + sc->symoff; //verifier offset
	str = data->ptr + sc->stroff;//verifier iffset
	length = symtab_lenght_64(tab, sc);
	if ((stab = alloc_symbol_64(length))) //non moins
	{
		i = 0;
		j = 0;
		while (i < sc->nsyms)
		{
			if(!(tab[i].n_type & N_STAB))
			{
				stab[j]->value = tab[i].n_value;
				stab[j]->type = get_type(tab[i], sectnames);
				stab[j]->name = str + tab[i].n_un.n_strx;
				j++;
			}
			i++;
		}
		quicksort_64(stab, 1, length);
		print_st64(stab);
	}
	else
		ft_putendl("stab allocation failed");
}
