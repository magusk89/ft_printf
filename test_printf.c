/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:26:21 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/12 02:04:49 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int	main(void)
{
	int		a;
	int		b;

	a = 0;
	b = 0;
	a = printf("This is %#5.3X an example.\n", 123);
	b = ft_printf("This is %#5.3X an example.\n", 123);
	printf("%d %d\n", a, b);
	return (0);
}
