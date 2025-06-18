/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:13:52 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/04 21:13:52 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a character to lowercase.
 * 
 * @param c The character to convert.
 * @return int The lowercase equivalent if applicable.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c = (c + 32);
		return (c);
	}
	else
		return (c);
}
