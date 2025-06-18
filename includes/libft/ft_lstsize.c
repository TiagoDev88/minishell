/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:20:09 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/11 16:39:01 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Calculates the size of the linked list.
 * 
 * This function traverses the entire list, counting the number of nodes 
 * until the end is reached 
 * (when a node's `next` pointer is `NULL`). It returns the total count of 
 * nodes in the list.
 * 
 * @param lst Pointer to the first node in the list.
 * @return size_t The number of nodes in the list.
 */
int	ft_lstsize(t_list *lst)
{
	t_list	*ptr;
	int		count;

	count = 0;
	ptr = lst;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}
