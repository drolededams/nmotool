/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:20:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/13 20:09:26 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	get_type_64(t_data *data, struct nlist_64 nl, char **sectnames)
{
	unsigned char lower;

	lower = 0;
	if (!(nl.n_type & N_EXT))
		lower = 32;
	if ((nl.n_type & N_EXT) && ((nl.n_type & N_TYPE) == N_UNDF) && (nl.n_type & N_PEXT))
		return ('C' + lower);// MH_OBJECT ONLY ??
	if ((nl.n_type & N_TYPE) == N_UNDF)//N_ext set or not to lower ?
		return ('U' + lower);
	if ((nl.n_type & N_TYPE) == N_ABS)
		return ('A' + lower);
	if ((nl.n_type & N_TYPE) == N_INDR)
		return ('I' + lower);
	if ((nl.n_type & N_TYPE) == N_SECT)
		return (get_sect(data, nl.n_sect - 1, sectnames, lower));
	return (' ');
}

char	get_sect(t_data *data, uint8_t n_sect, char **sectnames, char lower)
{
	data->error = data->error;
	if (!(ft_strcmp(sectnames[n_sect], "__text")))
			return ('T' + lower);
	if (!(ft_strcmp(sectnames[n_sect], "__data")))
			return ('D' + lower);
	if (!(ft_strcmp(sectnames[n_sect], "__bss")))
			return ('B' + lower);
	if (!(ft_strcmp(sectnames[n_sect], "__picsymbol_stub"))) //sure ??
			return ('I' + lower);
	if (!(ft_strcmp(sectnames[n_sect], "__symbol_stub"))) //sure ?? I deja geré ?
			return ('I' + lower);
	return ('S' + lower);
}

char	get_type_32(t_data *data, struct nlist nl, char **sectnames)
{
	unsigned char lower;

	lower = 0;
	if (!(nl.n_type & N_EXT))
		lower = 32;
	//if ((nl.n_type & N_EXT) && ((nl.n_type & N_TYPE) == N_UNDF))
	//	return ('C'); MH_OBJECT ONLY ??
	if ((nl.n_type & N_EXT) && ((nl.n_type & N_TYPE) == N_UNDF) && (nl.n_type & N_PEXT))
		return ('C' + lower);// MH_OBJECT ONLY ??
	if ((nl.n_type & N_TYPE) == N_UNDF)//N_ext set or not to lower ?
		return ('U' + lower);
	if ((nl.n_type & N_TYPE) == N_ABS)
		return ('A' + lower);
	if ((nl.n_type & N_TYPE) == N_INDR)
		return ('I' + lower);
	if ((nl.n_type & N_TYPE) == N_SECT)
		return (get_sect(data, nl.n_sect - 1, sectnames, lower));
	return (' ');
}
