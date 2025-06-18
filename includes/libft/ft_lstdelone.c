/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:47:14 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/12 19:47:14 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Deletes a single node from the list.
 * 
 * This function frees the content of a node by calling the provided
 *  `del` function 
 * and then frees the node itself. It does not modify the structure of
 *  the list, 
 * so the node must be removed separately if needed.
 * 
 * @param lst Pointer to the node to be deleted.
 * @param del Pointer to a function that deletes the content of the node.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}
