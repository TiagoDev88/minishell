/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:32:16 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/11 16:19:49 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Adds a new node to the front of the list.
 * 
 * This function inserts a new node at the beginning of the list by setting 
 * the `next` pointer 
 * of the new node to point to the current head of the list. Then, it updates 
 * the head of the list 
 * to point to the new node, effectively making it the first node.
 * 
 * @param lst Pointer to the pointer of the first node in the list.
 * @param new Pointer to the new node to be added.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}
