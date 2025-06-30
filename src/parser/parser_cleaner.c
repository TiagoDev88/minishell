/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:31:28 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/28 13:42:05 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Contains all functions to clean all memory allocated in 
	main struct T_CMD and sub structures
*/

#include "../../includes/minishell.h"

// Clean cmd_args**
int	cmd_clean_split(char **split, int status)
{
	int	i;

	if (!split)
		return (status);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (status);
}

// Clean t_redir*
void	redir_clean(t_redir **redir)
{
	t_redir	*curr;
	t_redir	*tmp;

	if (!(*redir) || !redir)
		return ;
	curr = *redir;
	while (curr)
	{
		tmp = curr->next;
		free(curr->filename);
		free(curr);
		curr = tmp;
	}
	*redir = NULL;
}

// Main cleaner function. 
int	cmd_clear(t_cmd **lst, int status)
{
	t_cmd	*curr;
	t_cmd	*tmp;

	if (!lst || !*lst)
		return (status);
	curr = *lst;
	while (curr)
	{
		cmd_clean_split(curr->cmd_args, 0);
		redir_clean(&curr->redir_in);
		redir_clean(&curr->redir_out);
		ft_lstclear(&curr->args_lst, &free);
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*lst = NULL;
	return (status);
}
