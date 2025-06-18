/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:45:38 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/11 16:46:07 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Returns the last node of the list.
 * 
 * This function traverses the list starting from the head, moving through 
 * each node 
 * until it reaches the last one (the node where `next` is `NULL`).
 * 
 * @param lst Pointer to the first node in the list.
 * @return t_list* Pointer to the last node in the list, or NULL if the list
 *  is empty.
 */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	if (lst == NULL)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}
