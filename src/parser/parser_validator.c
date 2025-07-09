/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:35:47 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/09 14:18:33 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Contain functions to validate Prompt pipe and redirects syntax.
*/

// Print redirects syntax errors.
int	print_redir_sintax_err(t_token *curr, int status)
{
	if (!curr->next)
		ft_putstr_fd(ERR_TOKEN_AFTER, 2);
	else if (curr->next->type == TOKEN_REDIR_OUT)
		ft_putstr_fd(ERR_NEAR_REDIR_OUT, 2);
	else if (curr->next->type == TOKEN_REDIR_IN)
		ft_putstr_fd(ERR_NEAR_REDIR_IN, 2);
	else if (curr->next->type == TOKEN_APPEND)
		ft_putstr_fd(ERR_NEAR_APPEND, 2);
	else if (curr->next->type == TOKEN_HEREDOC)
		ft_putstr_fd(ERR_NEAR_HEREDOC, 2);
	else if (curr->next->type == TOKEN_PIPE)
		ft_putstr_fd(ERR_NEAR_PIPE, 2);
	return (status);
}

// Validate pipe and send error
int	is_valid_pipe(t_token **prev, t_token **curr)
{
	if (!prev || !(*curr)->next || (*curr)->next->type == TOKEN_PIPE)
	{
		ft_putstr_fd(ERR_NEAR_PIPE, 2);
		return (0);
	}
	*prev = *curr;
	*curr = (*curr)->next;
	return (1);
}

// Validate redirects TOKENS
int	is_valid_redirect(t_token *curr)
{
	if (!curr->next)
		return (print_redir_sintax_err(curr, 0));
	else if (curr->next->type != TOKEN_WORD)
		return (print_redir_sintax_err(curr, 0));
	return (1);
}
