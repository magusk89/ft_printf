# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 22:58:19 by alebarbo          #+#    #+#              #
#    Updated: 2025/05/09 23:16:18 by alebarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror -ggdb -c
SRC = ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putunbr.c ft_puthex.c ft_putmem.c
OBJ = $(SRC:.c=.o)
NAME = libftprintf.a

.PHONY: all re fclean clean

all: $(NAME)

re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJ)

$(NAME): $(OBJ)
	ar rc $@ $^

$(OBJ): $(SRC)
	$(CC) $^

