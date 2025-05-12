/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:55:20 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/11 20:09:08 by alebarbo         ###   ########.fr       */
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

int	ft_putstr(const char *s, t_flags *flags)
{
	int		char_counter;
	int		len;

	char_counter = 0;
	if (flags->precision >= 0 && flags->precision < ft_strlen(s))
		len = flags->precision;
	else
		len = ft_strlen(s);
	if (flags->bitflag & DASH)
	{
		char_counter += write(1, s, len);
		char_counter += ft_width_print(flags->width - len);
	}
	else
	{
		char_counter += ft_width_print(flags->width - len);
		char_counter += write(1, s, len);
	}
	return (char_counter);
}
