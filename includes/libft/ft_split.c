/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:59:50 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/10 15:02:48 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while ((*str == c) && *str)
			str++;
		if (*str != c && *str)
			count++;
		while ((*str != c) && *str)
			str++;
	}
	return (count);
}

static void	free_array(char **ptr, int i)
{
	while (i--)
		free(ptr[i]);
	free(ptr);
}

static char	**copy_words(char **ptr, char const *s, int words, char c)
{
	int		i;
	int		start;
	int		in_word;
	char	*new_str;

	i = 0;
	start = 0;
	while (i < words)
	{
		while (s[start] == c)
			start++;
		in_word = start;
		while (s[in_word] != c && s[in_word])
			in_word++;
		new_str = ft_substr(s, start, (in_word - start));
		if (!new_str)
		{
			free_array(ptr, i);
			return (NULL);
		}
		ptr[i] = new_str;
		start = in_word;
		i++;
	}
	return (ptr);
}

/**
 * @brief Splits a string into an array of strings using a delimiter.
 * 
 * @param s The string to split.
 * @param c The delimiter character.
 * @return char** An array of strings, NULL-terminated.
 */
char	**ft_split(char const *s, char c)
{
	int		words;
	char	**ptr;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	ptr = malloc(sizeof(char *) * (words + 1));
	if (!ptr)
		return (NULL);
	ptr = copy_words(ptr, s, words, c);
	if (!ptr)
		return (NULL);
	ptr[words] = NULL;
	return (ptr);
}
