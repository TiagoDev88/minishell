/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:57:00 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/11 16:19:00 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Creates a new node for a linked list.
 * 
 * This function allocates memory for a new node of type `t_list` and 
 * initializes 
 * the content of the node with the provided value. The `next` pointer of the 
 * new node 
 * is set to `NULL`, indicating that it is the last node in the list at the 
 * moment of creation.
 * 
 * @param content Pointer to the content to be placed in the new node.
 * @return t_list* Pointer to the newly created node, or NULL if memory 
 * allocation fails.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new_element;

	new_element = malloc(sizeof(t_list));
	if (!new_element)
		return (NULL);
	new_element->content = content;
	new_element->next = NULL;
	return (new_element);
}
