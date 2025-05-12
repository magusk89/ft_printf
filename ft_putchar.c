/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:54:29 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/11 22:29:32 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_width_print(int len)
{
	int		char_counter;

	char_counter = 0;
	while (len > 0)
	{
		char_counter += write(1, " ", 1);
		len--;
	}
	return (char_counter);
}

int	ft_putchar(int c, t_flags *flags)
{
	int				char_counter;
	unsigned char	buffer;

	char_counter = 0;
	buffer = (unsigned char) c;
	if (flags->bitflag & DASH)
	{
		char_counter += write(1, &buffer, 1);
		char_counter += ft_width_print(flags->width - 1);
	}
	else
	{
		char_counter += ft_width_print(flags->width - 1);
		char_counter += write(1, &buffer, 1);
	}
	return (char_counter);
}
