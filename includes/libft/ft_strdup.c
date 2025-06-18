/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:13:23 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/08 11:49:13 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Duplicates a string.
 * 
 * @param s The string to duplicate.
 * @return char* The newly allocated copy of the string.
 */
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(s);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	len = 0;
	while (s[len])
	{
		tmp[len] = s[len];
		len++;
	}
	tmp[len] = '\0';
	return (tmp);
}
