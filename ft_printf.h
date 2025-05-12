/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:57:17 by alebarbo          #+#    #+#             */
/*   Updated: 2025/05/11 23:16:48 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define DASH 1
# define ZERO 2
# define HASH 4
# define SPACE 8
# define PLUS 16
# include <stdarg.h>
# include <unistd.h>

typedef struct s_flags
{
	char	bitflag;
	int		width;
	int		precision;
}			t_flags;

int	ft_printf(const char *format, ...);
int	ft_strlen(const char *s);
int	ft_nbrlen(int nbr);
int	ft_atoi(const char *nptr);
int	ft_putchar(int c, t_flags *flags);
int	ft_putstr(const char *s, t_flags *flags);
int	ft_putnbr(int nbr, t_flags *flags);
int	ft_putunbr(unsigned int nbr, t_flags *flags);
int	ft_puthex(unsigned int hex, t_flags *flags, char conversion);
int	ft_putmem(void *p, t_flags *flags);

#endif
