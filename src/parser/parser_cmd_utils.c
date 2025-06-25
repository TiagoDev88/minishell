/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 01:17:32 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/25 01:09:49 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_create_node(t_token **prev, t_token **curr)
{
	t_cmd	*node;
	t_token	*tmp;
	int		cmd_args;
	int		i;

	if (!(*curr))
		return (NULL);
	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->redir_in = NULL;
	node->redir_out = NULL;
	tmp = *curr;
	cmd_args = 0;
	while (tmp && tmp->type == TOKEN_WORD) // Calculate amount of args cmd will have - CMD + ARGS OR FLAGS
	{
		cmd_args++;
		tmp = tmp->next;
	}
	node->cmd = malloc(sizeof(char *) * (cmd_args + 1)); // Allocate **cmd to receive cmd + args or flags
	if (!node->cmd)
		return (NULL);
	i = 0;
	while ((*curr) && (*curr)->type == TOKEN_WORD) // Copy token values to array of strings -> **cmd.
	{
		node->cmd[i] = ft_strdup((*curr)->value);
		if (!node->cmd[i])
			return (NULL);
		i++;
		*prev = *curr;
		*curr = (*curr)->next;
	}
	node->cmd[cmd_args] = NULL;
	return (node);
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

void	cmd_clean_split(char **split)
{
	int	i;

	if (*split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	*split = NULL;
}

int cmd_clean_cmds(t_cmd **lst, int status)
{
	t_cmd	*curr;
	t_cmd	*tmp;

	if (*lst)
	{
		curr = *lst;
		while (curr)
		{
			cmd_clean_split(curr->cmd);
			tmp = curr->next;
			free(curr);
			curr = tmp;
		}
	}
	*lst = NULL;
	return (status);
}

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

int add_redir(t_redir **redir_lst, t_token **curr, t_token **prev)
{
	t_redir *new;

	if (!(*curr)->next || (*curr)->next->type != TOKEN_WORD)
		return (print_sintax_err((*curr), 0));
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
	if (*prev && (*prev)->next)
		*curr = (*prev)->next;
	else
		*curr = NULL;
	return (1);
}

int	add_cmd(t_cmd **cmd_lst, t_token **prev, t_token **curr)
{
	t_cmd	*new;

	new = cmd_create_node(prev, curr); // Go through all words
	if (!new)
		return (0);
	cmd_add_back(cmd_lst, new);
	while (*curr && (*curr)->type != TOKEN_PIPE) // Looking for the end of tokens or a pipe
	{
		if ((*curr)->type == TOKEN_REDIR_IN || (*curr)->type == TOKEN_HEREDOC)
		{
			if (!add_redir(&(*cmd_lst)->redir_in, curr, prev))
				return (0);
		}
		else
		{
			if (!add_redir(&(*cmd_lst)->redir_out, curr, prev))
				return (0);
		}
	}
	return (1);
}
