/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:21:00 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/16 18:09:28 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		main(int ac, char **av)
{
	t_data	*data;

	if ((data = (t_data*)malloc(sizeof(t_data))))
	{
		if (ac == 1)
			data->error = open_mmap("a.out", 0, data);
		else if (ac == 2)
			data->error = open_mmap(av[1], 0, data);
		else
			multi_open(data, ac, av);
	}
	else
	{
		ft_putendl_fd("malloc struct data failed", STDERR_FILENO);
		return (0);
	}
	if (data->error)
		return (put_error(data));
	return (0);
}

void	multi_open(t_data *data, int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		data->error = open_mmap(av[i++], 1, data);
		if (data->error && data->error != 3)
			put_error(data);
	}
	data->error = 0;
}
