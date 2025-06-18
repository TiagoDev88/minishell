/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:32:40 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/09 17:13:52 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies memory from source to destination.
 * 
 * @param dest Destination buffer.
 * @param src Source buffer.
 * @param n Number of bytes to copy.
 * @return void* Pointer to dest.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p_dest;
	unsigned char	*p_src;

	if (!dest && !src)
		return (NULL);
	p_dest = (unsigned char *) dest;
	p_src = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	return (dest);
}
