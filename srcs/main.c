/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:21:00 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/13 12:34:53 by dgameiro         ###   ########.fr       */
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
			data->error = open_mmap("a.out", 0, data);
		else if (ac == 2)
			data->error = open_mmap(av[i], 0, data);
		else
		{
			while (i < ac)//print filename if plusieurs et a.out case
			{
				data->error = open_mmap(av[i++], 1, data);
				if (data->error && data->error != 3)
					put_error(data);
			}
			data->error = 0;
		}
	}
	else
	{
		ft_putendl("malloc struct data failed");
		return(0);
	}
	if (data->error)
		return(put_error(data));
	return(0);
}
