/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:22:54 by dgameiro          #+#    #+#             */
/*   Updated: 2018/04/18 12:34:28 by dgameiro         ###   ########.fr       */
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
# define MOD_SIZE_64 8
# define MOD_SIZE 4

typedef struct		s_symbol_64
{
	uint64_t	value;
	char		type;
	char		*name;
}					t_symbol_64;

typedef struct		s_data
{
	void		*ptr;
	size_t		filesize;
	char		*filename;
	size_t		offset;
	int			libstatic;
	int			swap;
	int			multi;
	uint32_t	fat;
	uint32_t	nfat;
	uint32_t	nsects;
	uint32_t	error;
}					t_data;

void				multi_open(t_data *data, int ac, char **av);
void				init_data(t_data *data, int multi, char *file);
uint32_t			open_mmap(char *file, int multi, t_data *data);
struct load_command	*search_symtab(uint32_t ncmds, struct load_command *lc,
		t_data *data, uint32_t modsize);
uint32_t			error_file(char *str, t_data *data, int fd);
uint32_t			error_i_file(t_data *data, int fd);
uint32_t			error_directory(t_data *data, int fd);
void				nm_process(t_data *data);
void				mach_o_process(t_data *data);
void				parse_mach_o_64(t_data *data, uint32_t magic);
char				**get_sectnames_64(t_data *data, struct load_command *lc,
		uint32_t ncmds);
void				get_symtab_64(t_data *data, struct symtab_command *sc,
		char **sectnames);
void				print_st(t_data *data, t_symbol_64 **stab, int length);
void				quicksort_64(t_symbol_64 **stab,
		uint32_t first, uint32_t last);
uint32_t			split_64(t_symbol_64 **stab, uint32_t first,
		uint32_t last, uint32_t piv);
char				get_type_64(t_data *data, struct nlist_64 nl,
		char **sectnames);
char				get_sect(t_data *data, uint32_t n_sect, char **sectnames,
		char lower);
t_symbol_64			**alloc_symbol_64(uint32_t nsyms);
uint32_t			symtab_lenght_64(struct nlist_64 *tab,
		struct symtab_command *sc, t_data *data);
void				print_value(uint64_t value, char *hex, int i);
void				parse_mach_o_32(t_data *data, uint32_t magic);
char				**get_sectnames_32(struct load_command *lc, uint32_t ncmds,
		t_data *data);
uint32_t			symtab_lenght_32(struct nlist *tab,
		struct symtab_command *sc, t_data *data);
void				get_symtab_32(t_data *data, struct symtab_command *sc,
		char **sectnames);
char				get_type_32(t_data *data, struct nlist nl,
		char **sectnames);
void				parse_fat(t_data *data, uint32_t magic);
unsigned long		to_swap(unsigned long value, t_data *data);
unsigned long		swap_bit(unsigned long value);
uint64_t			to_swap_64(uint64_t value, t_data *data);
uint64_t			swap_bit_64(uint64_t value);
int					swap_cpu(int value, t_data *data);
void				swap_stab(t_symbol_64 **stab, uint32_t i, uint32_t j);
void				fat_process(struct fat_header *header, t_data *data);
int					search_x86_64(t_data *data, struct fat_arch *fa,
		uint32_t nfat_arch);
void				print_arch(t_data *data);
int					is_static(t_data *data);
void				static_lib_process(t_data *data);
int					header_lib_check(t_data *data);
size_t				filename_lenght(t_data *data);
size_t				get_filesize(t_data *data);
int					offset_check(t_data *data, size_t size);
void				parse_lib(t_data *data);
void				parse_lib_64(t_data *data);
int					put_error(t_data *data);
void				print_lib_name(t_data *data, size_t len);
void				lib_process(t_data *data);
void				fill_sect_tab_64(struct load_command *lc,
		char **sectnames, uint32_t j, uint32_t k);
void				search_seg_64(t_data *data, struct load_command *lc,
		uint32_t ncmds, char **sectnames);
void				add_nsect_64(t_data *data, struct load_command *cur,
		uint32_t offset);
char				**create_sectnames_64(t_data *data,
		struct load_command *lc, uint32_t ncmds);
void				add_nsect_32(t_data *data, struct load_command *cur,
		uint32_t offset);
char				**create_sectnames_32(t_data *data,
		struct load_command *lc, uint32_t ncmds);
void				search_seg_32(t_data *data, struct load_command *lc,
		uint32_t ncmds, char **sectnames);
void				fill_sect_tab_32(struct load_command *lc,
		char **sectnames, uint32_t j, uint32_t k);
void				fill_stab_64(t_data *data, struct symtab_command *sc,
		t_symbol_64 **stab, char **sectnames);
void				fill_stab_32(t_data *data, struct symtab_command *sc,
		t_symbol_64 **stab, char **sectnames);
void				free_data(t_data *data);
void				free_filename(t_data *data);
void				free_sectnames(char **sectnames);
void				free_stab(t_symbol_64 **stab);
#endif
