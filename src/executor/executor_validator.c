/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 01:02:36 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/15 23:23:26 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * has_cmd - Checks if there is at least one TOKEN_WORD starting at *curr.
 * @curr: Pointer to the current token pointer.
 *
 * Advances the token pointer while tokens are TOKEN_WORD.
 *
 * Return: 1 if one or more TOKEN_WORD tokens were found, 0 otherwise.
 */
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

/**
 * validate_abs_cmd - Validates an absolute or relative command path.
 * @cmd_path: Command path string.
 * @shell: Pointer to the shell structure (used for error handling).
 *
 * Checks if the command path exists, is not a directory, and is executable.
 * Prints appropriate error messages and sets exit codes on failure.
 *
 * Return: 1 if valid, 0 otherwise.
 */
int	validate_abs_cmd(char *cmd_path, t_shell *shell)
{
	struct stat	sb;

	if (stat(cmd_path, &sb) != 0)
	{
		print_cmd_err(cmd_path, 1, 127, shell);
		return (0);
	}
	if (S_ISDIR(sb.st_mode))
	{
		print_cmd_err(cmd_path, 0, 126, shell);
		return (0);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		print_cmd_err(cmd_path, 1, 126, shell);
		return (0);
	}
	return (1);
}

/**
 * is_valid_cmd - Validates if a command is executable or built-in.
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 *
 * Resets any previous command exit code.
 * If the command is a built-in, returns success immediately.
 * If command contains a slash, treats as absolute/relative path and validates.
 * Otherwise, attempts to resolve command path in PATH environment.
 *
 * Return: 1 if command is valid and executable, 0 otherwise.
 */
int	is_valid_cmd(t_shell *shell, t_cmd *cmd)
{
	if (shell->exec.cmd_exit_code)
		shell->exec.cmd_exit_code = 0;
	if (is_built_in(cmd->cmd_args[0]))
		return (1);
	if (ft_strchr(cmd->cmd_args[0], '/'))
	{
		cmd->cmd_path = ft_strdup(cmd->cmd_args[0]);
		if (!cmd->cmd_path)
			exit_clean(shell, ENOMEM);
		if (!validate_abs_cmd(cmd->cmd_path, shell))
			return (0);
	}
	else
		cmd->cmd_path = get_cmd_path(shell, cmd->cmd_args[0]);
	if (!cmd->cmd_path)
		return (0);
	return (1);
}

/**
 * validate_and_open_files - Validates redirection tokens and opens files.
 * @curr_token: Pointer to the current token pointer.
 * @shell: Pointer to the shell structure.
 *
 * Iterates over redirection tokens, attempts to open files accordingly.
 * Handles memory errors by terminating the shell cleanly.
 * On file open errors, reports and returns failure.
 *
 * Return: 1 on success, 0 if file open error detected.
 */
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
		if (*curr_token && (*curr_token)->type == TOKEN_WORD
			&& ((*curr_token)->next && is_redirect((*curr_token)->next)))
			*curr_token = (*curr_token)->next;
	}
	return (1);
}
