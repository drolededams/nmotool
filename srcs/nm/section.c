/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:28:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/23 15:26:58 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

char	**get_sectnames_32(struct load_command *lc, uint32_t ncmds,
t_data *data)
{
	uint32_t			i;
	struct load_command	*cur;
	uint32_t			offset;

	i = 0;
	data->nsects = 0;
	cur = lc;
	offset = sizeof(struct mach_header);
	while (i++ < ncmds && !data->error)
	{
		add_nsect_32(data, cur, offset);
		if (i != ncmds && offset_check(data, offset +
		to_swap(cur->cmdsize, data) + sizeof(struct load_command)))
		{
			offset += to_swap(cur->cmdsize, data);
			cur = (void*)cur + to_swap(cur->cmdsize, data);
		}
	}
	return (create_sectnames_32(data, lc, ncmds));
}

void	add_nsect_32(t_data *data, struct load_command *cur, uint32_t offset)
{
	struct segment_command *sc;

	sc = NULL;
	if (to_swap(cur->cmd, data) == LC_SEGMENT &&
			offset_check(data, offset + sizeof(struct segment_command)))
	{
		sc = (struct segment_command*)cur;
		data->nsects += to_swap(sc->nsects, data);
	}
}

char	**create_sectnames_32(t_data *data, struct load_command *lc,
uint32_t ncmds)
{
	char	**sectnames;

	if ((sectnames = (char**)malloc(sizeof(char*) * (data->nsects))) != NULL &&
			!data->error)
	{
		search_seg_32(data, lc, ncmds, sectnames);
		return (sectnames);
	}
	return (NULL);
}

void	search_seg_32(t_data *data, struct load_command *lc, uint32_t ncmds,
		char **sectnames)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	k;
	uint32_t	offset;

	i = 0;
	k = 0;
	offset = sizeof(struct mach_header);
	while (i++ < ncmds)
	{
		if (to_swap(lc->cmd, data) == LC_SEGMENT)
		{
			j = 0;
			while (j++ < to_swap(((struct segment_command*)lc)->nsects,
						data) && !data->error)
			{
				if (offset_check(data,
							offset + sizeof(struct segment_command) + (j - 1) *
							sizeof(struct section)))
					fill_sect_tab_32(lc, sectnames, j, k++);
			}
		}
		offset += to_swap(lc->cmdsize, data);
		lc = (i != ncmds) ? (void*)lc + to_swap(lc->cmdsize, data) : lc;
	}
}

void	fill_sect_tab_32(struct load_command *lc, char **sectnames,
uint32_t j, uint32_t k)
{
	struct section *section;

	j--;
	section = (struct section*)((void*)lc +
	sizeof(struct segment_command) + j * sizeof(struct section));
	sectnames[k] = section->sectname;
}
