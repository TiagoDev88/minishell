/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:01:28 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/12 20:01:28 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Iterates over the list and applies a function to each node.
 * 
 * This function iterates through the list, starting from the first node,
 *  and applies 
 * the provided function `f` to each node's content.
 * 
 * @param lst Pointer to the first node in the list.
 * @param f Pointer to a function to apply to each node's content.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;

	if (lst == NULL || f == NULL)
		return ;
	ptr = lst;
	while (ptr != NULL)
	{
		f(ptr->content);
		ptr = ptr->next;
	}
}
