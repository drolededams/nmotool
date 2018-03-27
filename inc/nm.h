/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:22:54 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/27 14:25:35 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef NM_H
# define NM_H
# include "../libft/includes/libft.h"
# include <stdint.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

void	open_mmap(char *file);
void	error_file(char *str, char*file, int fd);
void	parse_mach_o_64(void *ptr);
void	nm_process(void *ptr);
void	mach_o_process(void *ptr);
void	parse_mach_o_64(void *ptr);
void	sort_symtab(void *ptr, struct symtab_command *sc);
#endif
