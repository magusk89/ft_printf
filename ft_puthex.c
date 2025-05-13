/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:55:50 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/13 18:35:46 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_precision_print(char *hex, t_flags *flags, char c)
{
	int		char_counter;

	char_counter = 0;
	if (flags->bitflag & HASH && c == 'x' && ft_strlen(hex) && *hex != '0')
		char_counter += write(1, "0x", 2);
	if (flags->bitflag & HASH && c == 'X' && ft_strlen(hex) && *hex != '0')
		char_counter += write(1, "0X", 2);
	while (flags->precision > ft_strlen(hex))
	{
		char_counter += write(1, "0", 1);
		flags->precision--;
	}
	return (char_counter);
}

static int	ft_flag_check(char *hex, t_flags *flags, char c)
{
	char	*tmp;

	if (c == 'X')
	{
		tmp = hex;
		while (*tmp)
		{
			if (*tmp >= 'a' && *tmp <= 'f')
				*tmp -= 32;
			tmp += 1;
		}
	}
	return (ft_precision_print(hex, flags, c));
}

static int	ft_width_print(char *hex, t_flags *flags, char c)
{
	int		char_counter;
	int		len;

	char_counter = 0;
	if (flags->bitflag & ZERO && flags->precision < 0)
		char_counter += ft_flag_check(hex, flags, c);
	if (flags->bitflag & HASH && *hex != '0')
		len = ft_strlen(hex) + 2;
	else
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

static int	ft_tohex(unsigned int nbr, t_flags *flags, char *hex)
{
	int		i;

	i = 19;
	hex[20] = 0;
	if (nbr == 0 && flags->precision == 0)
		return (20);
	while (nbr > 15)
	{
		hex[i] = "0123456789abcdef"[nbr % 16];
		nbr /= 16;
		i--;
	}
	hex[i] = "0123456789abcdef"[nbr % 16];
	return (i);
}

int	ft_puthex(unsigned int nbr, t_flags *flags, const char conversion)
{
	int		count[2];
	char	hex[21];

	count[0] = 0;
	count[1] = ft_tohex(nbr, flags, hex);
	if (flags->precision > ft_strlen(&hex[count[1]]))
		flags->width -= flags->precision - ft_strlen(&hex[count[1]]);
	if (flags->bitflag & DASH)
	{
		count[0] += ft_flag_check(&hex[count[1]], flags, conversion);
		count[0] += write(1, &hex[count[1]], ft_strlen(&hex[count[1]]));
		count[0] += ft_width_print(&hex[count[1]], flags, conversion);
	}
	else if (flags->bitflag & ZERO && flags->precision < 0)
	{
		count[0] += ft_width_print(&hex[count[1]], flags, conversion);
		count[0] += write(1, &hex[count[1]], ft_strlen(&hex[count[1]]));
	}
	else
	{
		count[0] += ft_width_print(&hex[count[1]], flags, conversion);
		count[0] += ft_flag_check(&hex[count[1]], flags, conversion);
		count[0] += write(1, &hex[count[1]], ft_strlen(&hex[count[1]]));
	}
	return (count[0]);
}
