/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:55:20 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/13 19:54:30 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_width_print(t_flags *flags)
{
	int		char_counter;

	char_counter = 0;
	while (flags->width > 0)
	{
		char_counter += ft_write_guard(" ", 1, flags);
		flags->width--;
	}
	return (char_counter);
}

static int	ft_empty_string(t_flags *flags)
{
	int		char_counter;

	char_counter = 0;
	if (flags->precision >= 0 && flags->precision < 6)
		char_counter += ft_width_print(flags);
	else if (flags->precision < 0 || flags->precision >= 6)
	{
		if (flags->bitflag & DASH)
		{
			char_counter += ft_write_guard("(null)", 6, flags);
			flags->width -= 6;
			char_counter += ft_width_print(flags);
		}
		else
		{
			flags->width -= 6;
			char_counter += ft_width_print(flags);
			char_counter += ft_write_guard("(null)", 6, flags);
		}
	}
	return (char_counter);
}

int	ft_putstr(char *s, t_flags *flags)
{
	int		char_counter;
	int		len;

	char_counter = 0;
	if (s == 0)
		return (ft_empty_string(flags));
	if (flags->precision >= 0 && flags->precision < ft_strlen(s))
		len = flags->precision;
	else
		len = ft_strlen(s);
	if (flags->bitflag & DASH)
	{
		char_counter += ft_write_guard(s, len, flags);
		flags->width -= len;
		char_counter += ft_width_print(flags);
	}
	else
	{
		flags->width -= len;
		char_counter += ft_width_print(flags);
		char_counter += ft_write_guard(s, len, flags);
	}
	return (char_counter);
}
