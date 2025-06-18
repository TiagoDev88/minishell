/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:43:33 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/05 15:15:20 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Moves memory from source to destination, handling overlap.
 * 
 * @param dest Destination buffer.
 * @param src Source buffer.
 * @param n Number of bytes to move.
 * @return void* Pointer to dest.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;

	if (!dest && !src)
		return (NULL);
	p_dst = (unsigned char *)dest;
	p_src = (unsigned char *)src;
	if (p_dst > p_src)
	{
		while (n > 0)
		{
			p_dst[n - 1] = p_src[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
