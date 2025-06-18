/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:01:15 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/12 20:01:15 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Clears the entire list.
 * 
 * This function iterates through the entire list, deleting each node by 
 * calling the `del` 
 * function to free the content and then freeing the node itself. After 
 * clearing all nodes, 
 * it sets the list pointer to NULL.
 * 
 * @param lst Pointer to the pointer of the first node in the list.
 * @param del Pointer to a function that deletes the content of each node.
 */
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*tmp;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		tmp = ptr->next;
		del(ptr->content);
		free(ptr);
		ptr = tmp;
	}
	*lst = NULL;
}
