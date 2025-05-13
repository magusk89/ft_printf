/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:55:50 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/13 20:04:43 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_width_print(t_flags *flags)
{
	int		char_counter;

	char_counter = 0;
	while (flags->width > 5)
	{
		char_counter += ft_write_guard(" ", 1, flags);
		flags->width--;
	}
	return (char_counter);
}

int	ft_putmem(uintptr_t nbr, t_flags *flags)
{
	int		char_counter;

	char_counter = 0;
	if (flags->bitflag & DASH && nbr == 0)
	{
		char_counter += ft_write_guard("(nil)", 5, flags);
		char_counter += ft_width_print(flags);
	}
	else if (nbr == 0)
	{
		char_counter += ft_width_print(flags);
		char_counter += ft_write_guard("(nil)", 5, flags);
	}
	else
		return (ft_printmem(nbr, flags));
	return (char_counter);
}
