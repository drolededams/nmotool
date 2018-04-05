/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:22:54 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/05 17:20:39 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
# include "../libft/includes/libft.h"
# include <stdint.h>
# include <stdio.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

typedef struct	s_symbol_64
{
	uint64_t	value;
	char		type;
	char		*name;
}				t_symbol_64;

void	test_64(void *ptr, struct symtab_command *sc);
void		open_mmap(char *file);
void		error_file(char *str, char*file, int fd);
void		nm_process(void *ptr, size_t filesize);
void		mach_o_process(void *ptr, size_t filesize);
void		parse_mach_o_64(void *ptr, size_t filesize);
void		sort_symtab_64(void *ptr, struct symtab_command *sc);
void		print_type(void *ptr, uint8_t sect);
char		**get_sectnames_64(struct load_command *lc, uint32_t ncmds);
void		get_symtab_64(void *ptr, struct symtab_command *sc, char **sectnames);
void		print_st64(t_symbol_64 **stab);
void		quicksort_64(t_symbol_64 **stab, uint32_t first, uint32_t last);
uint32_t	split_64(t_symbol_64 **stab, uint32_t first, uint32_t last, uint32_t piv);
char		get_type(struct nlist_64 nl, char **sectnames);
char		get_sect_64(uint8_t n_sect, char **sectnames);
t_symbol_64 **alloc_symbol_64(uint32_t nsyms);
char		*value_to_str_64(uint64_t value, char *hex);
void		open_i_mmap(char *file);
void		error_i_file(char*file, int fd);
#endif
