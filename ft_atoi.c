/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:02:45 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/09 23:39:56 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/******************************************************************
* @file ft_atoi.c
*
* Converts the initial portion of the string pointed to by \em nptr
* to int.
*
* @param nptr: string from which the integer will be extracted.
*
* @return Returns the converted value or 0 on error.
******************************************************************/

int	ft_atoi(const char *nptr)
{
	int		res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		sign = (nptr[i] == '+') - (nptr[i] == '-');
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}
