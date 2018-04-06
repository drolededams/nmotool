/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:24:53 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/06 10:26:53 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_st64(t_symbol_64 **stab)
{
	int i;
	char *s;

	i = 0;
	while (stab[i])
	{
		if (ft_strcmp(stab[i]->name, "radr://5614542"))
		{
			if (stab[i]->type == 'U')
				printf("                 ");
			else
			{
				s = value_to_str_64(stab[i]->value, "0123456789abcdef");
				printf("%s ", s);
				free(s);
			}
			printf("%c ", stab[i]->type);
			printf("%s\n", stab[i]->name);
		}
		i++;
	}
}

char		*value_to_str_64(uint64_t value, char *hex)
{
	char		*str;
	int			i;
	uint64_t	r;

	i = 16;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		ft_putendl("Probleme allocation");
	str[i] = '\0';
	while (value)
	{
		i--;
		r = value % 16;
		str[i] = hex[r];
		value /= 16;
	}
	while (i > 0)
	{
		i--;
		str[i] = '0';
	}
	return (str);
}
