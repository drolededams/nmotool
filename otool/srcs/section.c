/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 13:51:49 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/14 20:04:42 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	search_t_sec_64(t_data *data, struct load_command *lc, uint32_t ncmds)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	offset;

	i = 0;
	offset = sizeof(struct mach_header_64);
	data->sec = NULL;
	while (i++ < ncmds && !data->sec)
	{
		if (to_swap(lc->cmd, data) == LC_SEGMENT_64)
		{
			j = 0;
			while (j++ < to_swap(((struct segment_command_64*)lc)->nsects,
			data) && !data->error && !data->sec)
			{
				if (offset_check(data,
				offset + sizeof(struct segment_command_64) + (j - 1) *
				sizeof(struct section_64)))
					is_sec_64(data, lc, j);
			}
		}
		offset += to_swap(lc->cmdsize, data);
		lc = (i != ncmds) ? (void*)lc + to_swap(lc->cmdsize, data) : lc;
	}
}

void	is_sec_64(t_data *data, struct load_command *lc, uint32_t j)
{
	struct section_64 *section;

	section = (struct section_64*)((void*)lc +
		sizeof(struct segment_command_64) + (j - 1) *
			sizeof(struct section_64));
	if (ft_strequ(section->segname, "__TEXT") &&
		ft_strequ(section->sectname, "__text"))
		data->sec = (void*)section;
}

void	search_t_sec_32(t_data *data, struct load_command *lc, uint32_t ncmds)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	offset;

	i = 0;
	offset = sizeof(struct mach_header);
	data->sec = NULL;
	while (i++ < ncmds && !data->sec)
	{
		if (to_swap(lc->cmd, data) == LC_SEGMENT)
		{
			j = 0;
			while (j++ < to_swap(((struct segment_command*)lc)->nsects,
			data) && !data->error && !data->sec)
			{
				if (offset_check(data,
				offset + sizeof(struct segment_command) + (j - 1) *
				sizeof(struct section)))
					is_sec_32(data, lc, j);
			}
		}
		offset += to_swap(lc->cmdsize, data);
		lc = (i != ncmds) ? (void*)lc + to_swap(lc->cmdsize, data) : lc;
	}
}

void	is_sec_32(t_data *data, struct load_command *lc, uint32_t j)
{
	struct section *section;

	section = (struct section*)((void*)lc +
		sizeof(struct segment_command) + (j - 1) *
			sizeof(struct section));
	if (ft_strequ(section->segname, "__TEXT") &&
		ft_strequ(section->sectname, "__text"))
		data->sec = (void*)section;
}
