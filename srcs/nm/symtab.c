/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:06:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/23 15:27:28 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

void				get_symtab_32(t_data *data, struct symtab_command *sc,
char **sectnames)
{
	uint32_t		length;
	t_symbol_64		**stab;
	struct nlist	*tab;

	stab = NULL;
	if (!data->error && offset_check(data, to_swap(sc->symoff, data)))
		tab = data->ptr + data->offset + to_swap(sc->symoff, data);
	if (!data->error)
	{
		length = symtab_lenght_32(tab, sc, data);
		if ((stab = alloc_symbol_64(length)))
		{
			fill_stab_32(data, sc, stab, sectnames);
			if (!data->error)
			{
				quicksort_64(stab, 1, length);
				if (data->fat)
					print_arch(data);
				print_st(data, stab, 8);
			}
		}
		else
			ft_putendl("stab allocation failed");
	}
	free_stab(stab);
}

void				fill_stab_32(t_data *data, struct symtab_command *sc,
t_symbol_64 **stab, char **sectnames)
{
	uint32_t		i;
	uint32_t		j;
	char			*str;
	struct nlist	*tab;

	i = 0;
	j = 0;
	if (!data->error && offset_check(data, to_swap(sc->symoff, data)))
		tab = data->ptr + data->offset + to_swap(sc->symoff, data);
	if (!data->error && offset_check(data, to_swap(sc->stroff, data)))
		str = data->ptr + data->offset + to_swap(sc->stroff, data);
	while (i < to_swap(sc->nsyms, data) && !data->error)
	{
		if (offset_check(data, ((void*)&tab[i] - data->ptr) +
					sizeof(struct nlist) - data->offset) &&
				offset_check(data, ((void*)str - data->ptr) +
					to_swap(tab[i].n_un.n_strx, data) - data->offset) &&
				!(tab[i].n_type & N_STAB))
		{
			stab[j]->value = to_swap(tab[i].n_value, data);
			stab[j]->type = get_type_32(data, tab[i], sectnames);
			stab[j++]->name = str + to_swap(tab[i].n_un.n_strx, data);
		}
		i++;
	}
}

uint32_t			symtab_lenght_32(struct nlist *tab,
struct symtab_command *sc, t_data *data)
{
	uint32_t length;
	uint32_t i;

	length = 0;
	i = 0;
	while (i < to_swap(sc->nsyms, data) && offset_check(data,
	((void*)&tab[i] - data->ptr) + sizeof(struct nlist) - data->offset))
	{
		if (!(tab[i].n_type & N_STAB))
			length++;
		i++;
	}
	return (length);
}

struct load_command	*search_symtab(uint32_t ncmds, struct load_command *lc,
t_data *data, uint32_t modsize)
{
	uint32_t	i;
	uint32_t	offset;

	if (modsize == MOD_SIZE_64)
		offset = sizeof(struct mach_header_64) + sizeof(struct load_command);
	else
		offset = sizeof(struct mach_header) + sizeof(struct load_command);
	i = 0;
	while (i++ < ncmds && !data->error &&
			to_swap(lc->cmd, data) != LC_SYMTAB)
	{
		if ((to_swap(lc->cmdsize, data) % modsize) != 0)
			data->error = 2;
		if (i != ncmds && !data->error && offset_check(data,
		sizeof(struct load_command) + to_swap(lc->cmdsize, data)))
		{
			offset += to_swap(lc->cmdsize, data);
			lc = (void*)lc + to_swap(lc->cmdsize, data);
		}
	}
	return (lc);
}
