/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_guard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:04:45 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/13 20:07:02 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_guard(const char *format, int len, t_flags *flags)
{
	int		char_counter;

	char_counter = write(1, format, len);
	if (char_counter < 0)
		flags->guard = -1;
	return (char_counter);
}
