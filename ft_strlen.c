/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:29:21 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/10 14:28:28 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/******************************************************************
* @file ft_strlen.c
*
* Calculates the length of the string pointed to by \em s,
* excluding the terminating null byte ('\0').
*
* @param s: the string from which the length shall be
* calculated.
*
* @return Returns the number of bytes in the string pointed to by \em s.
******************************************************************/

int	ft_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
