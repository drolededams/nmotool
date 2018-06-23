/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:16:19 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/23 15:27:43 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

void		get_symtab_64(t_data *data, struct symtab_command *sc,
char **sectnames)
{
	uint32_t		length;
	t_symbol_64		**stab;
	struct nlist_64	*tab;

	stab = NULL;
	if (!data->error && offset_check(data, to_swap(sc->symoff, data)))
		tab = data->ptr + data->offset + to_swap(sc->symoff, data);
	if (!data->error)
	{
		length = symtab_lenght_64(tab, sc, data);
		if ((stab = alloc_symbol_64(length)))
		{
			fill_stab_64(data, sc, stab, sectnames);
			if (!data->error)
			{
				quicksort_64(stab, 1, length);
				print_st(data, stab, 16);
			}
		}
		else
			ft_putendl("stab allocation failed");
	}
	free_stab(stab);
}

void		fill_stab_64(t_data *data, struct symtab_command *sc,
t_symbol_64 **stab, char **sectnames)
{
	uint32_t		i;
	uint32_t		j;
	char			*str;
	struct nlist_64	*tab;

	i = 0;
	j = 0;
	if (!data->error && offset_check(data, to_swap(sc->symoff, data)))
		tab = data->ptr + data->offset + to_swap(sc->symoff, data);
	if (!data->error && offset_check(data, to_swap(sc->stroff, data)))
		str = data->ptr + data->offset + to_swap(sc->stroff, data);
	while (i < to_swap(sc->nsyms, data) && !data->error)
	{
		if (offset_check(data, ((void*)&tab[i] - data->ptr) +
					sizeof(struct nlist_64) - data->offset) &&
				offset_check(data, ((void*)str - data->ptr) +
					to_swap(tab[i].n_un.n_strx, data) - data->offset) &&
				!(tab[i].n_type & N_STAB))
		{
			stab[j]->value = to_swap_64(tab[i].n_value, data);
			stab[j]->type = get_type_64(data, tab[i], sectnames);
			stab[j++]->name = str + to_swap(tab[i].n_un.n_strx, data);
		}
		i++;
	}
}

uint32_t	symtab_lenght_64(struct nlist_64 *tab, struct symtab_command *sc,
t_data *data)
{
	uint32_t length;
	uint32_t i;

	length = 0;
	i = 0;
	while (i < to_swap(sc->nsyms, data) && offset_check(data,
	((void*)&tab[i] - data->ptr) + sizeof(struct nlist_64) - data->offset))
	{
		if (!(tab[i].n_type & N_STAB))
			length++;
		i++;
	}
	return (length);
}
