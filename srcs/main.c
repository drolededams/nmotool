/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:21:00 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/05 16:35:38 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac == 1)
		open_mmap("a.out");
	else if (ac == 2)
		open_mmap(av[i]);
	else
	{
		while (i < ac)//print filename if plusieurs et a.out case
			open_i_mmap(av[i++]);
	}
	return(0);
}
