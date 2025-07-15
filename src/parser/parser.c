/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:54:10 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/15 23:06:32 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * check_prompt_syntax - Checks the syntax of the input tokens and builds the command list.
 * @parser_s: Pointer to the parser structure (double pointer).
 * @cmds_lst: Pointer to the command list to be populated.
 * @tokens: Linked list of tokens parsed from the input line.
 *
 * Iterates through the tokens to validate syntax:
 * - Verifies correct use of pipes using is_valid_pipe().
 * - Checks redirect syntax (>, >>, <, <<) via is_valid_redirect().
 * - Constructs commands using add_cmd() for both WORD and redirection tokens.
 *
 * Return: 1 if syntax is valid, 0 otherwise.
*/
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

/**
 * update_underscore_exp - Updates the special '_' variable in the shell.
 * @parser_s: Pointer to the parser structure containing the command list.
 * @shell: Pointer to the shell structure where the underscore will be updated.
 *
 * Sets the shell's underscore variable to the last argument of the most recent command.
 * If no commands are present, sets it to an empty string.
 * This is often used to replicate shell behavior for the special "$_" variable.
 *
 * Exits the program with ENOMEM if memory allocation fails.
 */
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

/**
 * parser - Main parsing function that validates tokens and prepares commands.
 * @parser_s: Pointer to the parser structure, which tracks command list and pipe count.
 * @tokens: Linked list of tokens generated from the user input.
 * @shell: Pointer to the shell structure holding runtime state.
 *
 * Performs high-level validation:
 * - Handles edge case where only "." is passed as input.
 * - Calls check_prompt_syntax() to ensure command structure is valid.
 * - If there are no pipes, updates the shell's "_" variable with update_underscore_exp().
 *
 * Return: 1 on successful parsing, 0 if an error occurred.
 */
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
