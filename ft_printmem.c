/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:55:50 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/13 20:06:44 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_precision_print(char *hex, t_flags *flags)
{
	int		char_counter;

	char_counter = 0;
	char_counter += ft_write_guard("0x", 2, flags);
	while (flags->precision > ft_strlen(hex))
	{
		char_counter += ft_write_guard("0", 1, flags);
		flags->precision--;
	}
	return (char_counter);
}

static int	ft_width_print(char *hex, t_flags *flags)
{
	int		char_counter;
	int		len;

	char_counter = 0;
	if (flags->bitflag & ZERO && flags->precision < 0)
		char_counter += ft_write_guard("0x", 2, flags);
	len = ft_strlen(hex) + 2;
	while (flags->width > len)
	{
		if (flags->bitflag & ZERO && !(flags->bitflag & DASH)
			&& flags->precision < 0)
			char_counter += ft_write_guard("0", 1, flags);
		else
			char_counter += ft_write_guard(" ", 1, flags);
		flags->width--;
	}
	return (char_counter);
}

static int	ft_tohex(unsigned long int nbr, t_flags *flags, char *hex)
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

int	ft_printmem(unsigned long int nbr, t_flags *flags)
{
	int		ctr[2];
	char	hex[21];

	ctr[0] = 0;
	ctr[1] = ft_tohex(nbr, flags, hex);
	if (flags->precision > ft_strlen(&hex[ctr[1]]))
		flags->width -= flags->precision - ft_strlen(&hex[ctr[1]]);
	if (flags->bitflag & DASH)
	{
		ctr[0] += ft_precision_print(&hex[ctr[1]], flags);
		ctr[0] += ft_write_guard(&hex[ctr[1]], ft_strlen(&hex[ctr[1]]), flags);
		ctr[0] += ft_width_print(&hex[ctr[1]], flags);
	}
	else if (flags->bitflag & ZERO && flags->precision < 0)
	{
		ctr[0] += ft_width_print(&hex[ctr[1]], flags);
		ctr[0] += ft_write_guard(&hex[ctr[1]], ft_strlen(&hex[ctr[1]]), flags);
	}
	else
	{
		ctr[0] += ft_width_print(&hex[ctr[1]], flags);
		ctr[0] += ft_precision_print(&hex[ctr[1]], flags);
		ctr[0] += ft_write_guard(&hex[ctr[1]], ft_strlen(&hex[ctr[1]]), flags);
	}
	return (ctr[0]);
}
