/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:45:55 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/07 22:46:45 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Contain helper functions to construct *t_cmd main struct and sub structures
	in parser_cmd.c
*/

#include "../../includes/minishell.h"

// Creates an array of char* from a t_list* linked list.
int	lst_to_arr(t_list *args_lst, char ***cmd_args)
{
	t_list	*curr;
	int		cmd_args_size;
	int		i;

	cmd_args_size = ft_lstsize(args_lst);
	if (cmd_args_size == 0)
		return (0);
	*cmd_args = malloc(sizeof(char *) * (cmd_args_size + 1));
	if (!*cmd_args)
		return (0);
	curr = args_lst;
	i = 0;
	while (curr)
	{
		(*cmd_args)[i] = ft_strdup(curr->content);
		if (!(*cmd_args)[i])
			return (cmd_clean_split(*cmd_args, 0));
		curr = curr->next;
		i++;
	}
	(*cmd_args)[cmd_args_size] = NULL;
	return (1);
}

int	save_cmd_args(t_list **args_lst, t_token **prev, t_token **curr)
{
	t_list	*new;
	char	*arg;

	while (*curr && (*curr)->type == TOKEN_WORD)
	{
		arg = ft_strdup((*curr)->value);
		if (!arg)
			return (0);
		new = ft_lstnew(arg);
		if (!new)
		{
			free(arg);
			ft_lstclear(args_lst, &free);
			return (0);
		}
		ft_lstadd_back(args_lst, new);
		*prev = *curr;
		*curr = (*curr)->next;
	}
	return (1);
}

// Push node to the end of t_redir* linked list.
void	redir_add_back(t_redir **redir_lst, t_redir *new)
{
	t_redir	*curr;

	if (!(*redir_lst))
		*redir_lst = new;
	else
	{
		curr = *redir_lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

// Create a *t_redir node. t_redir saves redirect tokens
// and his info like type and filename -> FILE or DELIMIT for heredoc
int	add_redir(t_redir **redir_lst, t_token **prev, t_token **curr)
{
	t_redir	*new;

	if (!is_valid_redirect(*curr))
		return (0);
	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->next = NULL;
	new->type = (*curr)->type;
	new->filename = ft_strdup((*curr)->next->value);
	redir_add_back(redir_lst, new);
	if (!new->filename)
		return (0);
	*prev = (*curr)->next;
	if (*prev && (*prev)->next != NULL)
		*curr = (*prev)->next;
	else
		*curr = NULL;
	return (1);
}

int	save_cmd_redirects(t_cmd *cmd, t_token **prev, t_token **curr)
{
	while (*curr)
	{
		if ((*curr)->type == TOKEN_REDIR_IN
			|| (*curr)->type == TOKEN_HEREDOC)
		{
			if (!add_redir(&cmd->redir_in, prev, curr))
				return (0);
		}
		else if ((*curr)->type == TOKEN_REDIR_OUT
			|| (*curr)->type == TOKEN_APPEND)
		{
			if (!add_redir(&cmd->redir_out, prev, curr))
				return (0);
		}
		else
			break ;
	}
	return (1);
}
