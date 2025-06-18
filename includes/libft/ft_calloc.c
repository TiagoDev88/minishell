/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:12:11 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/09 13:52:59 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates memory based on the nmemb and size and fills it with null's.
 * 
 * @param nmemb Number of elements.
 * @param size Size of each element.
 * @return void* Pointer to the allocated memory.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			i;
	unsigned char	*tmp;

	if (size != 0 && (nmemb > (size_t)(-1) / size))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	tmp = (unsigned char *)ptr;
	i = 0;
	while (i < nmemb * size)
	{
		tmp[i] = 0;
		i++;
	}
	return (ptr);
}
