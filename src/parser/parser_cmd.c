/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 01:17:32 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/26 23:01:31 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_create_node(void)
{
	t_cmd	*t_cmd_new;

	t_cmd_new = malloc(sizeof(t_cmd));
	if (!t_cmd_new)
		return (NULL);
	t_cmd_new->next = NULL;
	t_cmd_new->redir_in = NULL;
	t_cmd_new->redir_out = NULL;
	t_cmd_new->args_lst = NULL;
	t_cmd_new->cmd_args = NULL;
	return (t_cmd_new);
}

void	cmd_add_back(t_cmd	**lst, t_cmd *new)
{
	t_cmd	*curr;

	if (!new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		curr = *lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

int	add_mode_two(t_cmd **cmd_lst, t_token **prev, t_token **curr)
{
	t_cmd	*new;

	new = cmd_create_node(); // Go through all words
	if (!new)
		return (0);
	cmd_add_back(cmd_lst, new);
	if (!save_cmd_args(&new->args_lst, prev, curr))
		return (0);
	if (!save_cmd_redirects(new, prev, curr))
		return (0);
	if (!save_cmd_args(&new->args_lst, prev, curr))
		return (0);
	return (lst_to_arr(new->args_lst, &new->cmd_args));
}

int	add_mode_one(t_cmd **cmd_lst, t_token **prev, t_token **curr)
{
	t_cmd	*new;

	new = cmd_create_node(); // Go through all words
	if (!new)
		return (0);
	if (!save_cmd_redirects(new, prev, curr))
		return (0);
	if (*curr && (*curr)->type == TOKEN_WORD)
	{
		cmd_add_back(cmd_lst, new);
		if (!save_cmd_args(&new->args_lst, prev, curr))
			return (0);
		return (lst_to_arr(new->args_lst, &new->cmd_args));	
	}
	redir_clean(&new->redir_in);
	redir_clean(&new->redir_out);
	free(new);
	return (1);
}


int	add_cmd(t_cmd **cmd_lst, t_token **prev, t_token **curr, int mode)
{
	if (mode == 1)
	{
		if (!add_mode_one(cmd_lst, prev, curr))
			return (0);
	}
	else
	{
		if (!add_mode_two(cmd_lst, prev, curr))
			return (0);
	}
	return (1);
}
