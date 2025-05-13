/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:55:50 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/13 02:54:10 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_precision_print(int nbr, t_flags *flags)
{
	int		char_counter;

	char_counter = 0;
	while (flags->precision > ft_nbrlen(nbr))
	{
		char_counter += write(1, "0", 1);
		flags->precision--;
	}
	return (char_counter);
}

static int	ft_sign_flag(int nbr, t_flags *flags)
{
	int		char_counter;

	char_counter = 0;
	if (nbr < 0)
		char_counter += write(1, "-", 1);
	if (nbr >= 0 && flags->bitflag & PLUS)
		char_counter += write(1, "+", 1);
	if (nbr >= 0 && !(flags->bitflag & PLUS) && flags->bitflag & SPACE)
		char_counter += write(1, " ", 1);
	char_counter += ft_precision_print(nbr, flags);
	return (char_counter);
}

static int	ft_width_print(int nbr, t_flags *flags)
{
	int		char_counter;
	int		len;

	char_counter = 0;
	if (nbr == 0 && flags->precision == 0)
		len = 0;
	else
		len = ft_nbrlen(nbr);
	if (nbr < 0 || flags->bitflag & SPACE || flags->bitflag & PLUS)
		len++;
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

static int	ft_printnbr(int nbr, int empty_flag, t_flags *flags)
{
	int		char_counter[2];
	char	buffer;

	char_counter[0] = 0;
	char_counter[1] = 0;
	if (nbr == 0 && empty_flag == 0 && flags->precision == 0)
		return (0);
	char_counter[1] = 1;
	if (nbr == -2147483648)
		return (char_counter[0] += write(1, "2147483648", 10));
	nbr *= (nbr > 0) - (nbr < 0);
	if (nbr <= 9)
	{
		buffer = nbr + '0';
		char_counter[0] += write(1, &buffer, 1);
	}
	else
	{
		char_counter[0] += ft_printnbr(nbr / 10, char_counter[1], flags);
		buffer = (nbr % 10) + '0';
		char_counter[0] += write(1, &buffer, 1);
	}
	return (char_counter[0]);
}

int	ft_putnbr(int nbr, t_flags *flags)
{
	int		char_counter;

	char_counter = 0;
	if (flags->precision > ft_nbrlen(nbr))
		flags->width -= flags->precision - ft_nbrlen(nbr);
	if (flags->bitflag & DASH)
	{
		char_counter += ft_sign_flag(nbr, flags);
		char_counter += ft_printnbr(nbr, 0, flags);
		char_counter += ft_width_print(nbr, flags);
	}
	else if (flags->bitflag & ZERO && flags->precision < 0)
	{
		char_counter += ft_sign_flag(nbr, flags);
		char_counter += ft_width_print(nbr, flags);
		char_counter += ft_printnbr(nbr, 0, flags);
	}
	else
	{
		char_counter += ft_width_print(nbr, flags);
		char_counter += ft_sign_flag(nbr, flags);
		char_counter += ft_printnbr(nbr, 0, flags);
	}
	return (char_counter);
}
