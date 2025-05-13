# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 22:58:19 by alebarbo          #+#    #+#              #
#    Updated: 2025/05/13 02:48:41 by alebarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror -ggdb -c
SRC = ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putunbr.c ft_puthex.c ft_putmem.c ft_strlen.c ft_nbrlen.c ft_atoi.c ft_printmem.c
OBJ = $(SRC:.c=.o)
NAME = libftprintf.a

.PHONY: all re fclean clean

all: $(NAME)

bonus: all

re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJ)

$(NAME): $(OBJ)
	ar rc $@ $^

$(OBJ): $(SRC)
	$(CC) $^

