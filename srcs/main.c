/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:21:00 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/30 11:31:43 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac < 2)
		ft_putendl("usage : ft_nm + args");
	while (i < ac)//print filename if plusieurs et a.out case
		open_mmap(av[i++]);
	return(1);
}
