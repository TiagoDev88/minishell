/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:22:17 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/15 22:22:17 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Prints a memory address (pointer) in hexadecimal format.
 * 
 * @param ptr Pointer to be printed.
 * @return int The number of characters printed.
 */
int	ft_putptr(void *ptr)
{
	unsigned long	addr;
	int				count;

	if (ptr == NULL)
		return (ft_printf_putstr("(nil)"));
	count = 0;
	addr = (unsigned long)ptr;
	count = count + ft_printf_putstr("0x");
	count = count + ft_putnbr_base(addr, "0123456789abcdef");
	return (count);
}
