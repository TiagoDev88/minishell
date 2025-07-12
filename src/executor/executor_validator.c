/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 01:02:36 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/12 00:32:33 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_built_in(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (0);
	return (!ft_strcmp(cmd, "cd") ||
			!ft_strcmp(cmd, "echo") ||
			!ft_strcmp(cmd, "env") ||
			!ft_strcmp(cmd, "exit") ||
			!ft_strcmp(cmd, "export") ||
			!ft_strcmp(cmd, "pwd") ||
			!ft_strcmp(cmd, "unset"));
}

int	is_redirect(t_token *token)
{
	return (token->type >= TOKEN_REDIR_OUT && token->type <= TOKEN_HEREDOC);
}

int	has_cmd(t_token **curr)
{
	t_token	*tmp;

	tmp = *curr;
	while (*curr && (*curr)->type == TOKEN_WORD)
		*curr = (*curr)->next;
	if (tmp != *curr)
		return (1);
	return (0);
}

void	validate_cmd(char *cmd_path, t_shell *shell)
{
	struct stat	sb;

	if (stat(cmd_path, &sb) != 0)
		print_cmd_err_exit(cmd_path, 1, 127, shell);
	if (S_ISDIR(sb.st_mode))
		print_cmd_err_exit(cmd_path, 0, 126, shell);
	if (access(cmd_path, X_OK) != 0)
		print_cmd_err_exit(cmd_path, 1, 126, shell);
}

int	validate_and_open_files(t_token **curr_token, t_shell *shell)
{
	int	exit_s;

	exit_s = 0;
	while (*curr_token && is_redirect(*curr_token))
	{
		exit_s = add_file(&shell->exec.files_container, \
			(*curr_token)->next->value, (*curr_token)->type, shell);
		if (exit_s == -1)
		{
			print_error_msg(NULL, strerror(ENOMEM), 1);
			exit_clean(shell, ENOMEM);
		}
		if (exit_s > 0)
			return (file_has_error(shell, curr_token, exit_s));
		*curr_token = (*curr_token)->next->next;
		if (*curr_token && (*curr_token)->type == TOKEN_WORD && ((*curr_token)->next
					&& is_redirect((*curr_token)->next)))
			*curr_token = (*curr_token)->next;
	}
	return (1);
}
