/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:54:10 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/07 22:47:00 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Check Prompt line syntax
static int	check_prompt_syntax(t_cmd **cmd_lst, t_token *tokens)
{
	t_token	*curr;
	t_token	*prev;

	if (!tokens)
		return (0);
	curr = tokens;
	prev = NULL;
	while (curr)
	{
		if (curr && curr->type == TOKEN_PIPE)
			if (!is_valid_pipe(&prev, &curr))
				return (0);
		if (curr && curr->type >= TOKEN_REDIR_OUT
			&& curr->type <= TOKEN_HEREDOC)
		{
			if (!is_valid_redirect(curr))
				return (0);
			if (!add_cmd(cmd_lst, &prev, &curr, 1))
				return (0);
		}
		if (curr && curr->type == TOKEN_WORD)
		{
			if (!add_cmd(cmd_lst, &prev, &curr, 2))
				return (0);
		}
	}
	return (1);
}

int	parser(t_parser *parser_s, t_token *tokens)
{
	if (!check_prompt_syntax(&parser_s->cmd_lst, tokens))
		return (0);
	return (1);
}
