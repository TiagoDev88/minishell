/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:35:47 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/15 23:08:29 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * print_redir_sintax_err - Prints syntax error messages related to redirection tokens.
 * @curr: Pointer to the current token (expected to be a redirection operator).
 * @status: Status code to return after printing the error.
 *
 * Prints a syntax error message to stderr depending on the type of the token
 * following a redirection operator (e.g., >, >>, <, <<).
 * This function handles common syntax mistakes such as missing filenames
 * or illegal tokens after a redirection.
 *
 * Return: The provided status code (usually 0 to indicate failure).
 */
int	print_redir_sintax_err(t_token *curr, int status)
{
	if (!curr->next)
		ft_putendl_fd(ERR_TOKEN_AFTER, 2);
	else if (curr->next->type == TOKEN_REDIR_OUT)
		ft_putendl_fd(ERR_NEAR_REDIR_OUT, 2);
	else if (curr->next->type == TOKEN_REDIR_IN)
		ft_putendl_fd(ERR_NEAR_REDIR_IN, 2);
	else if (curr->next->type == TOKEN_APPEND)
		ft_putendl_fd(ERR_NEAR_APPEND, 2);
	else if (curr->next->type == TOKEN_HEREDOC)
		ft_putendl_fd(ERR_NEAR_HEREDOC, 2);
	else if (curr->next->type == TOKEN_PIPE)
		ft_putendl_fd(ERR_NEAR_PIPE, 2);
	return (status);
}

/**
 * is_valid_pipe - Validates the syntax of a pipe token and updates parser state.
 * @prev: Pointer to the previous token pointer.
 * @curr: Pointer to the current token pointer (expected to be a pipe).
 * @n_pipes: Pointer to the number of pipes parsed so far.
 *
 * Ensures that the pipe is neither the first nor the last token,
 * and is not followed by another pipe.
 * If the pipe is valid, updates the previous and current token pointers
 * and increments the pipe count.
 * On error, prints a syntax error and returns 0.
 *
 * Return: 1 if the pipe is valid, 0 otherwise.
 */
int	is_valid_pipe(t_token **prev, t_token **curr, int *n_pipes)
{
	if (!prev || !(*curr)->next || (*curr)->next->type == TOKEN_PIPE)
	{
		ft_putendl_fd(ERR_NEAR_PIPE, 2);
		return (0);
	}
	*prev = *curr;
	*curr = (*curr)->next;
	(*n_pipes)++;
	return (1);
}

/**
 * is_valid_redirect - Validates that a redirection token is followed by a valid word.
 * @curr: Pointer to the current token (a redirection operator).
 *
 * Checks if the redirection is properly followed by a WORD token (e.g., a filename).
 * If not, prints an appropriate syntax error message.
 *
 * Return: 1 if the redirect is valid, 0 otherwise.
 */
int	is_valid_redirect(t_token *curr)
{
	if (!curr->next)
		return (print_redir_sintax_err(curr, 0));
	else if (curr->next->type != TOKEN_WORD)
		return (print_redir_sintax_err(curr, 0));
	return (1);
}
