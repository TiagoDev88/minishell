/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_proccess_struct.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:54:14 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/07 01:06:18 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_proccess_s(t_proccess **procc_lst)
{
	t_proccess	*curr;
	t_proccess	*tmp;

	curr = *procc_lst;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
}

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

t_proccess	*create_proccess(void)
{
	t_proccess	*new;

	new = malloc(sizeof(t_proccess));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}
