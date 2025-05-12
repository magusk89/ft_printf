/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:55:50 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/12 02:04:36 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_touphex(char *hex)
{
	while (*hex)
	{
		if (*hex >= 'a' && *hex <= 'z')
			*hex -= 32;
		hex += 1;
	}
}

static int	ft_precision_print(const char *hex, t_flags *flags, char c)
{
	int		char_counter;

	char_counter = 0;
	if (flags->bitflag & HASH || c == 'p')
	{
		while (flags->precision > ft_strlen(hex) - 2)
		{
			char_counter += write(1, "0", 1);
			flags->precision--;
		}
	}
	else
	{
		while (flags->precision > ft_strlen(hex))
		{
			char_counter += write(1, "0", 1);
			flags->precision--;
		}
	}
	return (char_counter);
}

static int	ft_width_print(const char *hex, t_flags *flags)
{
	int		char_counter;
	int		len;

	char_counter = 0;
	len = ft_strlen(hex);
	while (flags->width > len)
	{
		if (flags->bitflag & ZERO && !(flags->bitflag & DASH)
			&& flags->precision < 0)
			char_counter += write(1, "0", 1);
		else
			char_counter += write(1, " ", 1);
		flags->width--;
	}
	return (char_counter);
}

static int	ft_tohex(unsigned int nbr, t_flags *flags, const char c, char *hex)
{
	int		i;

	i = 19;
	hex[20] = 0;
	if (nbr == 0 && flags->precision == 0)
		return (20);
	while (nbr > 9)
	{
		hex[i] = "0123456789abcdef"[nbr % 16];
		nbr /= 16;
		i--;
	}
	hex[i] = "0123456789abcdef"[nbr % 16];
	if (flags->bitflag & HASH || c == 'p')
	{
		hex[i - 1] = 'x';
		hex[i - 2] = '0';
		i -= 2;
	}
	if (c == 'X')
		ft_touphex(&hex[i]);
	return (i);
}

int	ft_puthex(unsigned int nbr, t_flags *flags, const char conversion)
{
	int		char_counter;
	char	hex[21];
	int		i;

	char_counter = 0;
	i = ft_tohex(nbr, flags, conversion, hex);
	if (flags->precision > ft_strlen(&hex[i]))
		flags->width -= flags->precision - ft_strlen(&hex[i]);
	if (flags->bitflag & DASH)
	{
		char_counter += ft_precision_print(&hex[i], flags, conversion);
		char_counter += write(1, hex, ft_strlen(&hex[i]));
		char_counter += ft_width_print(&hex[i], flags);
	}
	else if (flags->bitflag & ZERO && flags->precision < 0)
	{
		char_counter += ft_width_print(&hex[i], flags);
		char_counter += write(1, &hex[i], ft_strlen(&hex[i]));
	}
	else
	{
		char_counter += ft_width_print(&hex[i], flags);
		char_counter += ft_precision_print(&hex[i], flags, conversion);
		char_counter += write(1, &hex[i], ft_strlen(&hex[i]));
	}
	return (char_counter);
}
