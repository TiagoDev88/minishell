/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putchar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:24:17 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/15 15:41:06 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Writes a single character to standard output.
 * 
 * @param c The character to be printed.
 * @return int Always returns 1 (the number of characters printed).
 */
int	ft_printf_putchar(char c)
{
	int	count;

	count = 1;
	write(1, &c, 1);
	return (count);
}
