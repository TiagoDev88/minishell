/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:54:10 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/14 01:42:12 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Check Prompt line syntax
static int	check_prompt_syntax(t_parser **parser_s, t_cmd **cmds_lst, t_token *tokens)
{
	t_token	*curr;
	t_token	*prev;

	curr = tokens;
	prev = NULL;
	while (curr)
	{
		if (curr && curr->type == TOKEN_PIPE
			&& !is_valid_pipe(&prev, &curr, &(*parser_s)->n_pipes))
			return (0);
		if (curr && curr->type >= TOKEN_REDIR_OUT
			&& curr->type <= TOKEN_HEREDOC)
		{
			if (!is_valid_redirect(curr))
				return (0);
			if (!add_cmd(cmds_lst, &prev, &curr, 1))
				return (0);
		}
		if (curr && curr->type == TOKEN_WORD
			&& !add_cmd(cmds_lst, &prev, &curr, 2))
			return (0);
	}
	return (1);
}

void	update_underscore_exp(t_parser *parser_s, t_shell *shell)
{
	int	i;

	if (shell->underscore)
		free(shell->underscore);
	if (!parser_s->cmd_lst)
		shell->underscore = ft_strdup("");
	else
	{
		i = 0;
		while (parser_s->cmd_lst->cmd_args[i + 1])
			i++;
		shell->underscore = ft_strdup(parser_s->cmd_lst->cmd_args[i]);
	}
	if (!shell->underscore)
		exit_clean(shell, ENOMEM);
}

int	parser(t_parser *parser_s, t_token *tokens, t_shell *shell)
{
	if (!tokens)
		return (0);
	if ((tokens && !tokens->next)
		&& (ft_strlen(tokens->value) == 1 && tokens->value[0] == '.'))
	{
		print_error_msg(NULL, ERR_D, 1);
		shell->last_status_code = 2;
		return (0);
	}
	if (!check_prompt_syntax(&parser_s, &parser_s->cmd_lst, tokens))
		return (0);
	if (!parser_s->n_pipes)
		update_underscore_exp(parser_s, shell);
	return (1);
}
