/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:53:42 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/15 17:05:17 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Prints an unsigned integer to standard output.
 * 
 * @param nbr The unsigned integer to be printed.
 * @return int The number of characters printed.
 */
int	ft_putnbr_unsigned(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr > 9)
		count = count + ft_putnbr_unsigned(nbr / 10);
	count = count + ft_printf_putchar((nbr % 10) + 48);
	return (count);
}
