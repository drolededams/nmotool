/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:21:00 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/06 17:41:14 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		main(int ac, char **av)
{
	int		i;
	t_data	*data;

	if ((data = (t_data*)malloc(sizeof(t_data))))
	{
		i = 1;
		if (ac == 1)
			open_mmap("a.out", 0, data);
		else if (ac == 2)
			open_mmap(av[i], 0, data);
		else
		{
			while (i < ac)//print filename if plusieurs et a.out case
				open_mmap(av[i++], 1, data);
		}
	}
	return(0);
}
