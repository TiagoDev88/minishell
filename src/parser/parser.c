/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:54:10 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/23 00:21:35 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/token.h"

/* T_cmd Struct Utils */

void	clean_split(char **split)
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

int clean_cmds(t_cmd **lst, int status)
{
	t_cmd	*curr;
	t_cmd	*tmp;

	if (*lst)
	{
		curr = *lst;
		while (curr)
		{
			clean_split(curr->cmd);
			tmp = curr->next;
			free(curr);
			curr = tmp;
		}
	}
	return (status);
}

t_cmd	*create_node(t_token **curr)
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
		*curr = (*curr)->next;
	}
	node->cmd[cmd_args] = NULL;
	return (node);
}

void	add_back(t_cmd	**lst, t_cmd *new)
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


/*

	// TOKEN_PIPE can't be the first or last token
	// TOKEN_PIPE prev token must be a TOKEN WORD
	// TOKEN_PIPE next can't be a token. All the rest is valid
	// TOKEN_PIPE next token can be a redirect, append or heredoc but must be followed by a TOKEN WORD..
	// ..that will be a filename and a command that will be a TOKEN WORD too.

*/
int	is_valid_pipe(t_token *prev, t_token *curr)
{
	if (!prev || !curr->next)
			return (0);
	if (prev->type != TOKEN_WORD || curr->next->type == TOKEN_PIPE)
			return (0);
	if (curr->next->type >= TOKEN_REDIR_OUT && curr->next->type <= TOKEN_HEREDOC)
	{
		if (!curr->next->next || curr->next->next->type != TOKEN_WORD)
			return (0);
		if (!curr->next->next->next || curr->next->next->next->type != TOKEN_WORD)
			return (0);
	}
	return (1);
}

int	sum_parser_counts(t_token *prev, t_token **curr, t_parser *parser, t_cmd **lst)
{
	t_cmd	*new;

	if ((*curr)->type == TOKEN_WORD)
	{
		if (!prev || prev->type == TOKEN_PIPE || prev->type == TOKEN_WORD)
		{
			new = create_node(curr);
			if (!new)
				return (0);
			add_back(lst, new);
			parser->cmds++;
		}
	}
	else if ((*curr)->type == TOKEN_PIPE)
		parser->pipes++;
	else if ((*curr)->type == TOKEN_APPEND)
		parser->appends++;
	else if ((*curr)->type == TOKEN_HEREDOC)
		parser->heredoc++;
	else if ((*curr)->type == TOKEN_REDIR_IN)
		parser->redir_in++;
	else if ((*curr)->type == TOKEN_REDIR_OUT)
		parser->redir_out++;
	return (1);
}

int	check_line_sintax(t_token *tokens, t_parser *parser, t_cmd **lst)
{
	t_token	*curr;
	t_token	*prev;

	if (!tokens)
		return (0);
	curr = tokens;
	prev = NULL;
	while (curr)
	{
		// Validating pipes
		if (curr->type == TOKEN_PIPE)
			if (!is_valid_pipe(prev, curr))
				return (0);
		else if (curr->type >= TOKEN_REDIR_OUT && curr->type <= TOKEN_HEREDOC)
			if (!curr->next || curr->next->type != TOKEN_WORD)
				return (0);
		if (!sum_parser_counts(prev, &curr, parser, lst))
			return (0);
		if (curr)
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (1);
}

int	parser(t_cmd **lst, t_token *tokens)
{
	t_parser parser;

	ft_memset(&parser, 0, sizeof(parser));
	if (!check_line_sintax(tokens, &parser, lst))
		return (clean_cmds(lst, 0));
	return (1);
}
