/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:13:20 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/05 18:44:28 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of a character in a string.
 * 
 * @param s The string to search in.
 * @param c The character to find.
 * @return char* Pointer to the located character, or NULL if not found.
 */
char	*ft_strchr(const char *s, int c)
{
	char	convert_c;

	convert_c = (char) c;
	while (*s)
	{
		if (*s == convert_c)
			return ((char *) s);
		s++;
	}
	if (*s == convert_c)
		return ((char *) s);
	return (NULL);
}
