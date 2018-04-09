/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:20:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/09 11:35:47 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	get_type_64(struct nlist_64 nl, char **sectnames)
{
	unsigned char lower;

	lower = 0;
	if (!(nl.n_type & N_EXT))
		lower = 32;
	//if ((nl.n_type & N_EXT) && ((nl.n_type & N_TYPE) == N_UNDF))
	//	return ('C'); MH_OBJECT ONLY ??
	if ((nl.n_type & N_TYPE) == N_UNDF)//N_ext set or not to lower ?
		return ('U' + lower);
	if ((nl.n_type & N_TYPE) == N_ABS)
		return ('A' + lower);
	if ((nl.n_type & N_TYPE) == N_SECT)
		return (get_sect(nl.n_sect - 1, sectnames, lower));
	return (' ');
}

char	get_sect(uint8_t n_sect, char **sectnames, char lower)
{
	if (!(ft_strcmp(sectnames[n_sect], "__text")))
			return ('T' + lower);
	if (!(ft_strcmp(sectnames[n_sect], "__data")))
			return ('D' + lower);
	if (!(ft_strcmp(sectnames[n_sect], "__bss")))
			return ('B' + lower);
	if (!(ft_strcmp(sectnames[n_sect], "__picsymbol_stub")))
			return ('I' + lower);
	if (!(ft_strcmp(sectnames[n_sect], "__symbol_stub")))
			return ('I' + lower);
	return ('S' + lower);
}

char	get_type_32(struct nlist nl, char **sectnames)
{
	unsigned char lower;

	lower = 0;
	if (!(nl.n_type & N_EXT))
		lower = 32;
	//if ((nl.n_type & N_EXT) && ((nl.n_type & N_TYPE) == N_UNDF))
	//	return ('C'); MH_OBJECT ONLY ??
	if ((nl.n_type & N_TYPE) == N_UNDF)//N_ext set or not to lower ?
		return ('U' + lower);
	if ((nl.n_type & N_TYPE) == N_ABS)
		return ('A' + lower);
	if ((nl.n_type & N_TYPE) == N_SECT)
		return (get_sect(nl.n_sect - 1, sectnames, lower));
	return (' ');
}
