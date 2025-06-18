/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:57:46 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/11 11:31:38 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs a character to the given file descriptor.
 * 
 * @param c The character to output.
 * @param fd The file descriptor.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
