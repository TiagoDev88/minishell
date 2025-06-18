/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:13:30 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/05 16:00:11 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies up to size - 1 characters from src to dst,
 * @brief null-terminating the result.
 * 
 * @param dst The destination buffer.
 * @param src The source string.
 * @param size The size of the destination buffer.
 * @return size_t Total length of the string it tried to create (length of src).
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	i;

	len_src = 0;
	i = 0;
	while (src[len_src])
		len_src++;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len_src);
}
