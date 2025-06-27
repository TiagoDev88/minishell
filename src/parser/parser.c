/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:54:10 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/25 12:48:08 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*

	// TOKEN_PIPE can't be the first or last token
	// TOKEN_PIPE prev token must be a TOKEN WORD
	// TOKEN_PIPE next can't be a token. All the rest is valid
	// TOKEN_PIPE next token can be a redirect, append or heredoc but must be followed by a TOKEN WORD..
	// ..that will be a filename and a command that will be a TOKEN WORD too.

*/

int	print_sintax_err(t_token *curr, int status)
{
	if (!curr->next)
		ft_putstr_fd(ERR_SINTAX_NO_TOKEN_AFTER, 2);
	else if (curr->next->type == TOKEN_REDIR_OUT)
		ft_putstr_fd(ERR_SINTAX_NEAR_REDIR_OUT, 2);
	else if (curr->next->type == TOKEN_REDIR_IN)
		ft_putstr_fd(ERR_SINTAX_NEAR_REDIR_IN, 2);
	else if (curr->next->type == TOKEN_APPEND)
		ft_putstr_fd(ERR_SINTAX_NEAR_APPEND, 2);
	else if (curr->next->type == TOKEN_HEREDOC)
		ft_putstr_fd(ERR_SINTAX_NEAR_HEREDOC, 2);
	else if (curr->next->type == TOKEN_PIPE)
		ft_putstr_fd(ERR_SINTAX_NEAR_PIPE, 2);
	return (status);
}

int	is_valid_pipe(t_token *prev, t_token *curr)
{
	if (!prev || !curr->next)
		return (print_sintax_err(curr, 0));
	if (prev->type != TOKEN_WORD || curr->next->type == TOKEN_PIPE)
		return (print_sintax_err(curr, 0));
	if (curr->next->type >= TOKEN_REDIR_OUT && curr->next->type <= TOKEN_HEREDOC)
	{
		if (!curr->next->next || curr->next->next->type != TOKEN_WORD)
			return (print_sintax_err(curr, 0));
	}
	return (1);
}

int	check_line_sintax(t_cmd **cmd_lst, t_token *tokens)
{
	t_token	*curr;
	t_token	*prev;

	//printf("Checking line\n");
	if (!tokens)
		return (0);
	curr = tokens;
	prev = NULL;
	while (curr)
	{
		if (curr->type == TOKEN_PIPE)
		{
			if (!is_valid_pipe(prev, curr))
				return (0);
			prev = curr;
			curr = curr->next;
		}	
		if (curr->type == TOKEN_WORD)
		{
			if (!prev || prev->type == TOKEN_PIPE || prev->type == TOKEN_WORD)
				if (!add_cmd(cmd_lst, &prev, &curr))
					return (0);
		}
	}
	return (1);
}

int	parser(t_cmd **cmd_lst, t_token *tokens)
{
	if (!check_line_sintax(cmd_lst, tokens))
		return (0);
	return (1);
}
