/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:22:54 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/12 14:27:47 by dgameiro         ###   ########.fr       */
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
# include <mach-o/ranlib.h>
# include <mach-o/fat.h>
# include <mach/machine.h>

typedef struct	s_symbol_64
{
	uint64_t	value;
	char		type;
	char		*name;
	char		*object;
}				t_symbol_64;

typedef struct	s_data
{
	void		*ptr;
	size_t		filesize;
	char		*filename;
	size_t		offset;
	int			libstatic;
	int			swap;
	uint32_t	fat;
}				t_data;

void		open_mmap(char *file, int multi, t_data *data);
void		error_file(char *str, char*file, int fd);
void		nm_process(t_data *data);
void		mach_o_process(t_data *data);
void		parse_mach_o_64(t_data *data);
char		**get_sectnames_64(struct load_command *lc, uint32_t ncmds);
void		get_symtab_64(t_data *data, struct symtab_command *sc, char **sectnames);
void		print_st(t_symbol_64 **stab, int length);
void		quicksort_64(t_symbol_64 **stab, uint32_t first, uint32_t last);
uint32_t	split_64(t_symbol_64 **stab, uint32_t first, uint32_t last, uint32_t piv);
char		get_type_64(struct nlist_64 nl, char **sectnames);
char		get_sect(uint8_t n_sect, char **sectnames, char lower);
t_symbol_64 **alloc_symbol_64(uint32_t nsyms);
char		*value_to_str(uint64_t value, char *hex, int i);
void		error_i_file(char*file, int fd);
uint32_t	symtab_lenght_64(struct nlist_64 *tab, struct symtab_command *sc);
void		parse_mach_o_32(t_data *data);
char		**get_sectnames_32(struct load_command *lc, uint32_t ncmds, t_data *data);
uint32_t	symtab_lenght_32(struct nlist *tab, struct symtab_command *sc, t_data *data);
void		get_symtab_32(t_data *data, struct symtab_command *sc, char **sectnames);
char		get_type_32(struct nlist nl, char **sectnames);
void		parse_fat(t_data *data);
unsigned long	to_swap(unsigned long value, t_data *data);
unsigned long	swap_bit(unsigned long value);
int				swap_cpu(int value, t_data *data);
void			fat_process(struct fat_header *header, t_data *data);
void		print_arch(t_data *data);
int			is_static(t_data *data);
void		static_lib_process(t_data *data);
int			header_lib_check(t_data *data);
size_t		filename_lenght(t_data *data);
size_t		get_filesize(t_data *data);
int		offset_check(t_data *data, size_t size);
void	parse_lib(t_data *data);
void	parse_lib_64(t_data *data);
#endif
