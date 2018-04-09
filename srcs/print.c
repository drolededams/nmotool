/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:24:53 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/09 11:48:45 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_st(t_symbol_64 **stab, int length)
{
	int i;
	char *s;

	i = 0;
	while (stab[i])
	{
		if (ft_strcmp(stab[i]->name, "radr://5614542"))
		{
			if (stab[i]->type == 'U')
			{
				if (length == 16)
					printf("                 ");
				else
					printf("         ");
			}
			else
			{
				s = value_to_str(stab[i]->value, "0123456789abcdef", length);
				printf("%s ", s);
				free(s);
			}
			printf("%c ", stab[i]->type);
			printf("%s\n", stab[i]->name);
		}
		i++;
	}
}

char		*value_to_str(uint64_t value, char *hex, int i)
{
	char		*str;
	uint32_t	r;

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
