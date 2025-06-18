/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:13:55 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/04 21:13:55 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a character to uppercase.
 * 
 * @param c The character to convert.
 * @return int The uppercase equivalent if applicable.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c = (c - 32);
		return (c);
	}
	else
		return (c);
}
