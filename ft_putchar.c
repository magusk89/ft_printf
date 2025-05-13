/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:54:29 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/13 20:18:47 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_width_print(t_flags *flags)
{
	int		char_counter;

	char_counter = 0;
	flags->width--;
	while (flags->width > 0)
	{
		char_counter += ft_write_guard(" ", 1, flags);
		flags->width--;
	}
	return (char_counter);
}

int	ft_putchar(int c, t_flags *flags)
{
	int		char_counter;
	char	buffer;

	char_counter = 0;
	buffer = (char) c;
	if (flags->bitflag & DASH)
	{
		char_counter += ft_write_guard(&buffer, 1, flags);
		char_counter += ft_width_print(flags);
	}
	else
	{
		char_counter += ft_width_print(flags);
		char_counter += ft_write_guard(&buffer, 1, flags);
	}
	return (char_counter);
}
