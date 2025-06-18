/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:13:41 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/04 21:13:41 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates a substring in a string, within the first len characters.
 * 
 * @param big The string to search in.
 * @param little The substring to find.
 * @param len Maximum number of characters to search.
 * @return char* Pointer to the beginning of the located substring,
 * @return or NULL if not found.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[0])
		return ((char *)big);
	while ((i < len) && big[i])
	{
		j = 0;
		while ((i + j < len) && big[i + j] == little[j] && little[j])
			j++;
		if (!little[j])
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
