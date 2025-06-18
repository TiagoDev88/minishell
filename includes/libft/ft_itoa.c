/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:59:30 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/10 17:45:31 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_len(long int n)
{
	size_t	count;

	count = 0;
	if (n < 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	ft_format_number(long nbr, char *ptr, int count)
{
	int	start;
	int	end;

	start = 0;
	end = count - 1;
	if (nbr < 0)
	{
		ptr[0] = '-';
		nbr = -nbr;
		start = 1;
	}
	while (start <= end)
	{
		ptr[end] = '0' + (nbr % 10);
		nbr = nbr / 10;
		end--;
	}
	ptr[count] = '\0';
}

/**
 * @brief Converts an integer to a string.
 * 
 * @param n The integer to convert.
 * @return char* The newly allocated string representing the integer.
 */
char	*ft_itoa(int n)
{
	long	nbr;
	char	*ptr;
	int		count;

	nbr = n;
	if (nbr == 0)
	{
		ptr = ft_strdup("0");
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	count = count_len(n);
	ptr = malloc(sizeof(char) * (count + 1));
	if (!ptr)
		return (NULL);
	ft_format_number(nbr, ptr, count);
	return (ptr);
}
