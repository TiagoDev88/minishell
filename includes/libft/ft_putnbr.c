/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:58:37 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/15 16:57:04 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Prints a signed integer to standard output.
 * 
 * @param nbr The integer to be printed.
 * @return int The number of characters printed.
 */
int	ft_putnbr(int nbr)
{
	int	count;

	count = 0;
	if (nbr == -2147483648)
		count = count + ft_printf_putstr("-2147483648");
	else
	{
		if (nbr < 0)
		{
			count = count + ft_printf_putchar('-');
			nbr = -nbr;
		}
		if (nbr > 9)
			count = count + ft_putnbr(nbr / 10);
		count = count + ft_printf_putchar((nbr % 10) + 48);
	}
	return (count);
}
