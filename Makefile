# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/01 15:17:23 by mle-roy           #+#    #+#              #
#    Updated: 2014/05/01 20:28:30 by ael-kadh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_script
VERSION=1.0.3
CFLAGS=-Wall -Werror -Wextra -g3
INCLUDES=-I ./libft/includes
LIBS=-L ./libft -l ft -ltermcap

SRC=main.c move.c test.c m_strdup.c ft_termcaps.c

OBJ=$(SRC:.c=.o)

all: build $(NAME) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): $(OBJ) ./libft/libft.a
	gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c ./libft/includes
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

