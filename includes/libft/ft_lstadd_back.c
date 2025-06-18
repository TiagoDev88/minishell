/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:46:57 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/11 17:38:50 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Adds a new node to the end of the list.
 * 
 * This function traverses the list to find the last node and then sets its
 *  `next` pointer 
 * to point to the new node. The new node becomes the last node in the list.
 * 
 * @param lst Pointer to the pointer of the first node in the list.
 * @param new Pointer to the new node to be added.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}
