/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:00:37 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/09 15:00:16 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Joins two strings into a new string.
 * 
 * @param s1 First string.
 * @param s2 Second string.
 * @return char* The newly allocated joined string.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstring;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	newstring = malloc(sizeof(char) * ((len_s1 + len_s2) + 1));
	if (!newstring)
		return (NULL);
	newstring = ft_memcpy(newstring, s1, len_s1);
	i = 0;
	while (i < len_s2)
	{
		newstring[len_s1 + i] = s2[i];
		i++;
	}
	newstring[len_s1 + i] = '\0';
	return (newstring);
}
