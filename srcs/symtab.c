/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:06:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/16 16:41:47 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

uint32_t symtab_lenght_64(struct nlist_64 *tab, struct symtab_command *sc, t_data *data)
{
	uint32_t length;
	uint32_t i;

	length = 0;
	i = 0;
	while (i < to_swap(sc->nsyms, data) && offset_check(data, ((void*)&tab[i] - data->ptr) + sizeof(struct nlist_64) - data->offset))
	{
		if(!(tab[i].n_type & N_STAB))
			length++;
		i++;
	}
	return (length);
}

uint32_t symtab_lenght_32(struct nlist *tab, struct symtab_command *sc, t_data *data)
{
	uint32_t length;
	uint32_t i;

	length = 0;
	i = 0;
	while (i < to_swap(sc->nsyms, data) && offset_check(data, ((void*)&tab[i] - data->ptr) + sizeof(struct nlist) - data->offset))
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

	if (!data->error && offset_check(data, to_swap(sc->symoff, data)))
		tab = data->ptr + data->offset + to_swap(sc->symoff, data);
	if (!data->error && offset_check(data, to_swap(sc->stroff, data)))
		str = data->ptr + data->offset + to_swap(sc->stroff, data);
	if (!data->error)
	{
		length = symtab_lenght_64(tab, sc, data);
		if ((stab = alloc_symbol_64(length)))
		{
			i = 0;
			j = 0;
			while (i < to_swap(sc->nsyms, data) && !data->error)
			{
				if(offset_check(data, ((void*)&tab[i] - data->ptr) + sizeof(struct nlist_64) - data->offset) && offset_check(data, ((void*)str - data->ptr) + to_swap(tab[i].n_un.n_strx, data) - data->offset) && !(tab[i].n_type & N_STAB))
				{
					stab[j]->value = to_swap_64(tab[i].n_value, data);
					stab[j]->type = get_type_64(data, tab[i], sectnames);
					stab[j]->name = str + to_swap(tab[i].n_un.n_strx, data);
					j++;
				}
				i++;
			}
			if(!data->error)
			{
				quicksort_64(stab, 1, length);
				print_st(data, stab, 16);
			}
		}
		else
			ft_putendl("stab allocation failed");
	}
}

void	get_symtab_32(t_data *data, struct symtab_command *sc, char **sectnames)
{
	uint32_t i;
	uint32_t j;
	uint32_t length;
	t_symbol_64 **stab;
	char *str;
	struct nlist  *tab;

	if (!data->error && offset_check(data, to_swap(sc->symoff, data)))
		tab = data->ptr + data->offset + to_swap(sc->symoff, data);
	if (!data->error && offset_check(data, to_swap(sc->stroff, data)))
		str = data->ptr + data->offset + to_swap(sc->stroff, data);
	if (!data->error)
	{
		length = symtab_lenght_32(tab, sc, data);
		if ((stab = alloc_symbol_64(length)))
		{
			i = 0;
			j = 0;
			while (i < to_swap(sc->nsyms, data) && !data->error)
			{
				if(offset_check(data, ((void*)&tab[i] - data->ptr) + sizeof(struct nlist) - data->offset) && offset_check(data, ((void*)str - data->ptr) + to_swap(tab[i].n_un.n_strx, data) - data->offset) && !(tab[i].n_type & N_STAB))
				{
					stab[j]->value = to_swap(tab[i].n_value, data);
					stab[j]->type = get_type_32(data, tab[i], sectnames);
					stab[j]->name = str + to_swap(tab[i].n_un.n_strx, data);
					j++;
				}
				i++;
			}
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
}
