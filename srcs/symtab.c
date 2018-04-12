/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:06:22 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/12 18:47:40 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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

uint32_t symtab_lenght_32(struct nlist *tab, struct symtab_command *sc, t_data *data)
{
	uint32_t length;
	uint32_t i;

	length = 0;
	i = 0;
	while (i < to_swap(sc->nsyms, data))
	{
		if(!(to_swap(tab[i].n_type, data) & N_STAB))
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

	if (!data->error && offset_check(data, sc->symoff))
		tab = data->ptr + data->offset + sc->symoff; 
	if (!data->error && offset_check(data, sc->stroff))
		str = data->ptr + data->offset + sc->stroff;
	if (!data->error)
	{
		length = symtab_lenght_64(tab, sc);
		if ((stab = alloc_symbol_64(length)))
		{
			i = 0;
			j = 0;
			while (i < sc->nsyms)
			{
				if(!(tab[i].n_type & N_STAB))
				{
					stab[j]->value = tab[i].n_value;
					stab[j]->type = get_type_64(tab[i], sectnames);
					stab[j]->name = str + tab[i].n_un.n_strx;
					j++;
				}
				i++;
			}
			quicksort_64(stab, 1, length);
			print_st(data, stab, 16);
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

	tab = data->ptr + data->offset + to_swap(sc->symoff, data); //verifier offset
	str = data->ptr + data->offset + to_swap(sc->stroff, data);//verifier iffset
	length = symtab_lenght_32(tab, sc, data);
	if ((stab = alloc_symbol_64(length))) //non moins
	{
		i = 0;
		j = 0;
		while (i < to_swap(sc->nsyms, data))
		{
			if(!(to_swap(tab[i].n_type, data) & N_STAB))
			{
				stab[j]->value = to_swap(tab[i].n_value, data);
				stab[j]->type = get_type_32(tab[i], sectnames);
				stab[j]->name = str + to_swap(tab[i].n_un.n_strx, data);
				j++;
			}
			i++;
		}
		quicksort_64(stab, 1, length);
		if (data->fat)
			print_arch(data);
		print_st(data, stab, 8);
	}
	else
		ft_putendl("stab allocation failed");
}
