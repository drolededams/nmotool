# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/12 15:32:27 by dgameiro          #+#    #+#              #
#    Updated: 2018/04/18 18:16:56 by dgameiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Ilibft -Iinc -Wall -Wextra -Werror
SRC = main.c open.c ot_process.c parse.c print.c section.c free.c error.c \
	  swap.c fat_ut.c
OBJDIR = objs
VPATH = srcs

OBJ = $(patsubst %,$(OBJDIR)/%,$(SRC:.c=.o))

NAME = ft_otool

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
