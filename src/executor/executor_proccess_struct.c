/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_proccess_struct.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:54:14 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/15 23:27:32 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * clean_proccess_s - Frees and clears the entire linked list of processes.
 * @procc_lst: Pointer to the head of the t_proccess list.
 *
 * Iterates through the list, frees each node, and sets the list pointer to NULL.
 */
void	clean_proccess_s(t_proccess **procc_lst)
{
	t_proccess	*curr;
	t_proccess	*tmp;

	if (!procc_lst || !(*procc_lst))
		return ;
	curr = *procc_lst;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*procc_lst = NULL;
}

/**
 * procc_add_back - Adds a new process node to the end of the list.
 * @procc_lst: Pointer to the head of the t_proccess list.
 * @new_proccess: New t_proccess node to add.
 *
 * If the list is empty, sets the new node as the head.
 * Otherwise, appends it to the end.
 */
void	procc_add_back(t_proccess **procc_lst, t_proccess *new_proccess)
{
	t_proccess	*curr;

	if (!(*procc_lst))
		*procc_lst = new_proccess;
	else
	{
		curr = *procc_lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new_proccess;
	}
}

/**
 * create_proccess - Allocates and initializes a new t_proccess node.
 *
 * Allocates memory for a new t_proccess structure and initializes its
 * next pointer to NULL.
 * Prints an error message and returns NULL if memory allocation fails.
 *
 * Return: Pointer to the new t_proccess node, or NULL on failure.
 */
t_proccess	*create_proccess(void)
{
	t_proccess	*new;

	new = malloc(sizeof(t_proccess));
	if (!new)
	{
		print_error_msg(NULL, strerror(ENOMEM), 1);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}
