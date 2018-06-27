/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:22:54 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/23 18:45:46 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H
# include "../libft/includes/libft.h"
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/ranlib.h>
# include <mach-o/fat.h>
# include <mach/machine.h>
# define MOD_SIZE_64 8
# define MOD_SIZE 4

typedef struct	s_data
{
	void		*ptr;
	void		*sec;
	size_t		filesize;
	char		*filename;
	size_t		offset;
	int			libstatic;
	int			swap;
	int			multi;
	int			obj;
	uint64_t	exe;
	uint32_t	fat;
	uint32_t	nfat;
	uint32_t	nsects;
	uint32_t	error;
}				t_data;

void			multi_open(t_data *data, int ac, char **av);
uint32_t		open_mmap(char *file, int multi, t_data *data);
void			init_data(t_data *data, int multi, char *file);
void			ot_process(t_data *data);
int				offset_check(t_data *data, size_t size);
int				offset_check_sec(t_data *data, uint32_t offset, size_t size);
void			mach_o_process(t_data *data);
void			parse_mach_o_64(t_data *data, uint32_t magic);
void			parse_mach_o_32(t_data *data, uint32_t magic);
void			print_64(t_data *data);
void			print_32(t_data *data);
void			print_addr(uint64_t addr, char *hex, int i);
void			search_t_sec_64(t_data *data, struct load_command *lc,
		uint32_t ncmds);
void			is_sec_64(t_data *data, struct load_command *lc, uint32_t j);
void			free_filename(t_data *data);
void			free_data(t_data *data);
uint32_t		error_file(char *str, t_data *data, int fd);
uint32_t		error_i_file(t_data *data, int fd);
uint32_t		error_directory(t_data *data, int fd);
int				put_error(t_data *data);
unsigned long	to_swap(unsigned long value, t_data *data);
unsigned long	swap_bit(unsigned long value);
uint64_t		to_swap_64(uint64_t value, t_data *data);
uint64_t		swap_bit_64(uint64_t value);
void			search_t_sec_32(t_data *data, struct load_command *lc,
		uint32_t ncmds);
void			is_sec_32(t_data *data, struct load_command *lc, uint32_t j);
void			parse_fat(t_data *data, uint32_t magic);
void			fat_process(struct fat_header *header, t_data *data);
int				search_x86_64(t_data *data, struct fat_arch *fa,
		uint32_t nfat_arch);
void			lib_process(t_data *data);
void			static_lib_process(t_data *data);
int				header_lib_check(t_data *data);
size_t			filename_lenght(t_data *data);
size_t			get_filesize(t_data *data);
int				is_static(t_data *data);
void			parse_lib_64(t_data *data);
void			parse_lib(t_data *data);
void			print_lib_name(t_data *data, size_t len);
void			print_char(unsigned char c, char *hex, char *dest);
void			print_content(char *str, char *hex, char *dest, uint32_t n);
void			print_arch(t_data *data, struct section_64 *sec,
		uint32_t offset);
void			print_content_ppc(char *str, char *hex, char *dest, uint32_t n);
void			print_ppc(t_data *data, struct section *sec, uint32_t offset);
void			print_arch_32(t_data *data, struct section *sec,
		uint32_t offset);
void			print_normal_32(t_data *data, struct section *sec,
		uint32_t offset);
void			print_normal_64(t_data *data, struct section_64 *sec,
		uint32_t offset);
#endif
