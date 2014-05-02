# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/02 19:31:57 by mle-roy           #+#    #+#              #
#    Updated: 2014/05/02 19:31:57 by mle-roy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_script
VERSION=1.0.4
CFLAGS=-Wall -Werror -Wextra -g
INCLUDES=-I ./libft/includes
LIBS=-L ./libft -l ft

SRC=fill_script.c \
	ft_script.c \
	ft_termcaps.c \
	m_strdup.c \
	m_strjoinwsep.c \
	m_strnew.c \
	m_strsplit.c \
	m_strsub.c \
	main.c \
	move.c \
	script_cmd.c \

OBJ=$(SRC:.c=.o)

all: build $(NAME) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): $(OBJ) ./libft/libft.a
	gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c script.h ./libft/includes
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAME))
	@($(MAKE) -C ./libft fclean)

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\033[32m$(NAME)\033[00m]")

.PHONY: all build clean fclean re v

