/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:28:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/12 18:42:03 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char		**get_sectnames_64(t_data *data, struct load_command *lc, uint32_t ncmds)
{
	uint32_t			i;
	uint32_t			j;
	uint32_t			k;
	uint32_t			nsects;
	struct load_command	*cur;
	struct section_64	*section;
	char				**sectnames;
	uint32_t total_offset;

	i = 0;
	k = 0;
	nsects = 0;
	cur = lc;
	total_offset = sizeof(struct mach_header_64);
	while (i++ < ncmds && !data->error)
	{
		if (cur->cmd == LC_SEGMENT_64 && offset_check(data, total_offset + sizeof(struct segment_command_64)))
			nsects += ((struct segment_command_64*)cur)->nsects;
		if (offset_check(data, total_offset + cur->cmdsize + sizeof(struct load_command)))
		{
			total_offset += cur->cmdsize;
			cur = (void*)cur + cur->cmdsize;
		}
	}
	total_offset = sizeof(struct mach_header_64);
	if ((sectnames = (char**)malloc(sizeof(char*) * nsects - 1)) != NULL && !data->error)
	{
		i = 0;
		while (i < ncmds)
		{
			if (lc->cmd == LC_SEGMENT_64)
			{
				j = 0;
				while (j++ < ((struct segment_command_64*)lc)->nsects && !data->error)
				{
					if (offset_check(data, total_offset + sizeof(struct segment_command_64) + (j - 1) * sizeof(struct section_64)))
					{
						section = (struct section_64*)((void*)lc + sizeof(struct segment_command_64) + (j - 1) * sizeof(struct section_64));
						sectnames[k] = section->sectname;
						k++;
					}
				}
			}
			i++;
			total_offset += lc->cmdsize;
			lc = (void*)lc + lc->cmdsize;
		}
	}
	return (sectnames);
}

char		**get_sectnames_32(struct load_command *lc, uint32_t ncmds, t_data *data)
{
	uint32_t			i;
	uint32_t			j;
	uint32_t			k;
	uint32_t			nsects;
	struct load_command	*cur;
	struct section		*section;
	char				**sectnames;

	i = 0;
	k = 0;
	nsects = 0;
	cur = lc;
	while (i++ < ncmds)
	{
		if (to_swap(cur->cmd, data) == LC_SEGMENT)
			nsects += to_swap(((struct segment_command*)cur)->nsects, data);
		cur = (void*)cur + to_swap(cur->cmdsize, data);
	}
	if ((sectnames = (char**)malloc(sizeof(char*) * nsects - 1)) != NULL)
	{
		i = 0;
		while (i < ncmds)
		{
			if (to_swap(lc->cmd, data) == LC_SEGMENT)
			{
				j = 0;
				while (j++ < to_swap(((struct segment_command*)lc)->nsects, data))
				{
					section = (struct section*)((void*)lc + sizeof(struct segment_command) + (j - 1) * sizeof(struct section));
					sectnames[k] = section->sectname;
					k++;
				}
			}
			i++;
			lc = (void*)lc + to_swap(lc->cmdsize, data);
		}
	}
	return (sectnames);
}
