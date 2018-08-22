/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 13:27:41 by dgameiro          #+#    #+#             */
/*   Updated: 2018/08/20 13:33:46 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

void		print_arch_type(cpu_type_t cpu)
{
	if (cpu == CPU_TYPE_POWERPC)
		ft_putendl("ppc):");
	else if (cpu == CPU_TYPE_I386)
		ft_putendl("i386):");
	else if (cpu == CPU_TYPE_ANY)
		ft_putendl("any architecture):");
	else if (cpu == CPU_TYPE_X86)
		ft_putendl("x86):");
	else if (cpu == CPU_TYPE_X86_64)
		ft_putendl("x86_64):");
	else if (cpu == CPU_TYPE_ARM)
		ft_putendl("arm):");
	else if (cpu == CPU_TYPE_ARM64)
		ft_putendl("arm64):");
	else if (cpu == CPU_TYPE_MC98000)
		ft_putendl("m98k):");
	else if (cpu == CPU_TYPE_VAX)
		ft_putendl("vax):");
	else if (cpu == CPU_TYPE_POWERPC64)
		ft_putendl("ppc64):");
	else
		print_arch_type_2(cpu);
}

void		print_arch_type_2(cpu_type_t cpu)
{
	if (cpu == CPU_TYPE_MC680x0)
		ft_putendl("m68k):");
	else if (cpu == CPU_TYPE_HPPA)
		ft_putendl("hppa):");
	else if (cpu == CPU_TYPE_SPARC)
		ft_putendl("sparc):");
	else if (cpu == CPU_TYPE_MC88000)
		ft_putendl("m88k):");
	else if (cpu == CPU_TYPE_I860)
		ft_putendl("i860):");
}
