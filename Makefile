# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/12 15:32:27 by dgameiro          #+#    #+#              #
#    Updated: 2018/08/20 14:52:59 by dgameiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

SRC_NM_PATH = srcs/nm
SRC_OT_PATH = srcs/otool

SRC_NM = main.c error.c nm_process.c open.c parse_64.c symtab.c symtab_64.c \
	alloc.c type.c quicksort.c print.c section.c section_64.c lib_ut.c swap.c \
	fat_ut.c free.c print_arch.c

SRC_OT = main.c open.c ot_process.c parse.c print.c section.c free.c error.c \
	  swap.c fat_ut.c lib_ut.c print_32.c print_arch.c

OBJ_PATH = objs
OBJ_NM_PATH = objs/nm
OBJ_OT_PATH = objs/otool

CPPFLAGS = -Iinc

LDFLAGS = -Llibft
LDLIBS = -lft

NM = ft_nm
OTOOL = ft_otool

CC = gcc
CFLAGS = -Wall -Wextra -Werror

OBJ_NM = $(SRC_NM:.c=.o)
OBJ_OT = $(SRC_OT:.c=.o)

SRC_N = $(addprefix $(SRC_NM_PATH)/,$(SRC_NM))
OBJ_N = $(addprefix $(OBJ_NM_PATH)/,$(OBJ_NM))

SRC_O = $(addprefix $(SRC_OT_PATH)/,$(SRC_OT))
OBJ_O = $(addprefix $(OBJ_OT_PATH)/,$(OBJ_OT))

all: $(NM) $(OTOOL)

nm_ex: $(NM)

ot_ex: $(OTOOL)

$(NM): $(OBJ_N)
	@make -C libft
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OTOOL): $(OBJ_O)
	@make -C libft
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OBJ_NM_PATH)/%.o: $(SRC_NM_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_NM_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(OBJ_OT_PATH)/%.o: $(SRC_OT_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_OT_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@make clean -C libft
	@rm -fv $(OBJ_N)
	@rmdir $(OBJ_NM_PATH) 2> /dev/null || true
	@rm -fv $(OBJ_O)
	@rmdir $(OBJ_OT_PATH) 2> /dev/null || true
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean : clean
	@make fclean -C libft
	@rm -fv $(NM) $(OTOOL)

re : fclean all
