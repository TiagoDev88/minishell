/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:13:08 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/04 21:13:08 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fills a block of memory with a specific byte.
 * 
 * @param b The memory area to fill.
 * @param c The byte to fill with.
 * @param len Number of bytes to fill.
 * @return void* Pointer to the memory area b.
 */
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
