/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:20:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/05 16:36:04 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	get_type(struct nlist_64 nl, char **sectnames)
{
	//if ((nl.n_type & N_EXT) && ((nl.n_type & N_TYPE) == N_UNDF))
	//	return ('C'); MH_OBJECT ONLY ??
	if ((nl.n_type & N_TYPE) == N_UNDF)
		return ('U');
	if ((nl.n_type & N_TYPE) == N_ABS)
		return ('A');
	if ((nl.n_type & N_TYPE) == N_SECT)
		return (get_sect_64(nl.n_sect - 1, sectnames));
	return (' ');
}

char	get_sect_64(uint8_t n_sect, char **sectnames)
{
	if (!(ft_strcmp(sectnames[n_sect], "__text")))//convention __lower ?
			return ('T');
	if (!(ft_strcmp(sectnames[n_sect], "__data")))
			return ('D');
	if (!(ft_strcmp(sectnames[n_sect], "__bss")))
			return ('B');
	if (!(ft_strcmp(sectnames[n_sect], "__picsymbol_stub")))
			return ('I');
	if (!(ft_strcmp(sectnames[n_sect], "__symbol_stub")))
			return ('I');
	return ('S');
}
