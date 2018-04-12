# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/12 15:32:27 by dgameiro          #+#    #+#              #
#    Updated: 2018/04/12 14:00:14 by dgameiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Ilibft -Iinc -Wall -Wextra -Werror
SRC = main.c error.c nm_process.c open.c parse_64.c symtab.c alloc.c type.c \
	  quicksort.c print.c section.c lib_ut.c swap.c
OBJDIR = objs
VPATH = srcs

OBJ = $(patsubst %,$(OBJDIR)/%,$(SRC:.c=.o))

NAME = ft_nm

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) -Llibft/ -lft -o $@ $^


$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c -o $@ $< $(CFLAGS)

clean :
	@make clean -C libft
	@rm -rf $(OBJDIR)

fclean : clean
	@make fclean -C libft
	@rm -rf $(NAME)

re : fclean all
