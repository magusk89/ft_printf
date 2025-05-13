/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:55:50 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/13 19:59:42 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_unbrlen(unsigned int nbr)
{
	int		i;

	i = 1;
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static int	ft_precision_print(unsigned int nbr, t_flags *flags)
{
	int		char_counter;

	char_counter = 0;
	while (flags->precision > ft_unbrlen(nbr))
	{
		char_counter += ft_write_guard("0", 1, flags);
		flags->precision--;
	}
	return (char_counter);
}

static int	ft_width_print(unsigned int nbr, t_flags *flags)
{
	int		char_counter;
	int		len;

	char_counter = 0;
	if (nbr == 0 && flags->precision == 0)
		len = 0;
	else
		len = ft_unbrlen(nbr);
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

static int	ft_printnbr(unsigned int nbr, int empty_flag, t_flags *flags)
{
	int		char_counter[2];
	char	buffer;

	char_counter[0] = 0;
	char_counter[1] = 0;
	if (nbr == 0 && empty_flag == 0 && flags->precision == 0)
		return (0);
	char_counter[1] = 1;
	if (nbr <= 9)
	{
		buffer = nbr + '0';
		char_counter[0] += ft_write_guard(&buffer, 1, flags);
	}
	else
	{
		char_counter[0] += ft_printnbr(nbr / 10, char_counter[1], flags);
		buffer = (nbr % 10) + '0';
		char_counter[0] += ft_write_guard(&buffer, 1, flags);
	}
	return (char_counter[0]);
}

int	ft_putunbr(unsigned int nbr, t_flags *flags)
{
	int		char_counter;

	char_counter = 0;
	if (flags->precision > ft_unbrlen(nbr))
		flags->width -= flags->precision - ft_unbrlen(nbr);
	if (flags->bitflag & DASH)
	{
		char_counter += ft_precision_print(nbr, flags);
		char_counter += ft_printnbr(nbr, 0, flags);
		char_counter += ft_width_print(nbr, flags);
	}
	else if (flags->bitflag & ZERO && flags->precision < 0)
	{
		char_counter += ft_width_print(nbr, flags);
		char_counter += ft_printnbr(nbr, 0, flags);
	}
	else
	{
		char_counter += ft_width_print(nbr, flags);
		char_counter += ft_precision_print(nbr, flags);
		char_counter += ft_printnbr(nbr, 0, flags);
	}
	return (char_counter);
}
