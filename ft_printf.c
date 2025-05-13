/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:59:29 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/13 18:09:12 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_flag_flip(const char c, t_flags *flags)
{
	if (c == '-')
		flags->bitflag |= DASH;
	if (c == '0')
		flags->bitflag |= ZERO;
	if (c == '#')
		flags->bitflag |= HASH;
	if (c == ' ')
		flags->bitflag |= SPACE;
	if (c == '+')
		flags->bitflag |= PLUS;
}

static char	*ft_flag_check(const char *format, t_flags *flags)
{
	flags->bitflag = 0;
	flags->width = 0;
	flags->precision = -1;
	while (*format == '-' || *format == '0' || *format == '#'
		|| *format == ' ' || *format == '+')
	{
		ft_flag_flip(*format, flags);
		format += 1;
	}
	if (*format >= '1' && *format <= '9')
		flags->width = ft_atoi(format);
	while (*format >= '0' && *format <= '9')
		format += 1;
	if (*format == '.')
	{
		format += 1;
		flags->precision = ft_atoi(format);
		while (*format >= '0' && *format <= '9')
			format += 1;
	}
	return ((char *)format);
}

static int	ft_conversion(const char *format, va_list args_list, t_flags *flags)
{
	int		char_counter;

	char_counter = 0;
	if (*format == 'c')
		char_counter += ft_putchar(va_arg(args_list, int), flags);
	else if (*format == 's')
		char_counter += ft_putstr(va_arg(args_list, char *), flags);
	else if (*format == 'd' || *format == 'i')
		char_counter += ft_putnbr(va_arg(args_list, int), flags);
	else if (*format == 'u')
		char_counter += ft_putunbr(va_arg(args_list, unsigned int), flags);
	else if (*format == 'x' || *format == 'X')
		char_counter += ft_puthex(va_arg(args_list, unsigned int), flags,
				*format);
	else if (*format == 'p')
		char_counter += ft_putmem(va_arg(args_list, uintptr_t), flags);
	else
		char_counter += write(1, "%", 1);
	return (char_counter);
}

static int	ft_print_counter(const char *format, va_list args_list)
{
	t_flags	flags;
	int		char_counter;
	int		tmp;

	char_counter = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format += 1;
			format = ft_flag_check(format, &flags);
			tmp = ft_conversion(format, args_list, &flags);
		}
		else
			tmp = write(1, format, 1);
		if (tmp < 0)
			return (-1);
		char_counter += tmp;
		format += 1;
	}
	return (char_counter);
}

int	ft_printf(const char *format, ...)
{
	va_list	args_list;
	int		char_counter;

	char_counter = 0;
	if (!format || !*format)
		return (0);
	va_start(args_list, format);
	char_counter = ft_print_counter(format, args_list);
	va_end(args_list);
	return (char_counter);
}
