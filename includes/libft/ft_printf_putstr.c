/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:48:45 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/15 15:49:19 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Writes a string to standard output.
 * 
 * @param str Pointer to the string to be printed.
 * @return int The number of characters printed.
 */
int	ft_printf_putstr(char *str)
{
	int	count;

	if (!str)
		str = "(null)";
	count = 0;
	while (str[count])
	{
		ft_printf_putchar(str[count]);
		count++;
	}
	return (count);
}
