/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:01:38 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/12 20:01:38 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Creates a new list by applying a function to each node of the 
 * original list.
 * 
 * This function applies the function `f` to the content of each node in 
 * the original list, 
 * creating a new node for each result. It returns a new list with the 
 * transformed content.
 * 
 * @param lst Pointer to the first node in the list.
 * @param f Pointer to a function to apply to each node's content.
 * @param del Pointer to a function to delete content in case of failure.
 * @return t_list* Pointer to the new list, or NULL if memory allocation 
 * fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*node;
	void	*newcontent;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	newlist = NULL;
	while (lst != NULL)
	{
		newcontent = f(lst->content);
		node = ft_lstnew(newcontent);
		if (node == NULL)
		{
			del(newcontent);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, node);
		lst = lst->next;
	}
	return (newlist);
}
