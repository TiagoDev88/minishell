/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 01:02:36 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/10 00:19:22 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	while (*curr_token && ((*curr_token)->type >= TOKEN_REDIR_OUT
			&& (*curr_token)->type <= TOKEN_HEREDOC))
	{
		exit_s = add_file(&shell->exec.files_container, \
			(*curr_token)->next->value, (*curr_token)->type);
		if (exit_s == -1)
		{
			print_error_msg(NULL, strerror(ENOMEM), 1);
			exit_clean(shell, ENOMEM);
		}
		if (exit_s > 0)
		{
			g_exit_status = 1;
			print_file_err((*curr_token)->next->value, strerror(exit_s), 0);
			while (*curr_token && ((*curr_token)->type >= TOKEN_REDIR_OUT
					&& (*curr_token)->type <= TOKEN_HEREDOC))
				*curr_token = (*curr_token)->next->next;
			return (0);
		}
		*curr_token = (*curr_token)->next->next;
	}
	return (1);
}
