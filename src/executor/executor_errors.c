/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:06:44 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/22 15:24:24 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * file_has_error - Handles a file-related error during parsing redirections.
 * @shell: Pointer to the shell structure.
 * @curr_token: Pointer to the current token pointer in the token list.
 * @exit_status: The error code returned by system calls (e.g., errno).
 *
 * Prints the corresponding error message for the file, sets the shell's last
 * status code to 1, and advances the token pointer past all related redirection
 * tokens.
 *
 * Return: Always returns 0.
 */
int	file_has_error(t_shell *shell, t_token **curr_token, int exit_status)
{
	if (exit_status == 130)
		shell->last_status_code = 130;
	else if (exit_status == 131)
		shell->last_status_code = 0;
	else
	{
		shell->last_status_code = 1;
		print_file_err((*curr_token)->next->value, strerror(exit_status), 0);
	}
	while (*curr_token && is_redirect(*curr_token))
	{
		*curr_token = (*curr_token)->next->next;
		if (*curr_token && (*curr_token)->type == TOKEN_WORD
			&& ((*curr_token)->next && is_redirect((*curr_token)->next)))
			*curr_token = (*curr_token)->next;
	}
	return (0);
}

/**
 * print_error_msg - Prints an error message to standard error.
 * @arg: The argument or filename related to the error (can be NULL).
 * @error: The error description string.
 * @mode: Mode to control prefix printing (1 to print "bash: ", 0 otherwise).
 *
 * Prints the error message in the format:
 *  [bash:] arg: error\n
 */
void	print_error_msg(char *arg, char *error, int mode)
{
	if (mode == 1)
		ft_putstr_fd("bash: ", 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	if (error)
		ft_putendl_fd(error, 2);
}

/**
 * print_cmd_err - Prints a command execution error message and sets status.
 * @cmd: The command string that caused the error.
 * @mode: Mode to select between error messages for "not found" or "no access".
 * @exit_s: The exit status code to set in the shell.
 * @shell: Pointer to the shell structure.
 *
 * Depending on exit_s and mode, prints an appropriate error message like
 * "command not found", "No such file or directory", "Permission denied",
 * or "Is a directory". Also updates the shell's last status code and the
 * exec command exit code.
 */
void	print_cmd_err(char *cmd, int mode, int exit_s, t_shell *shell)
{
	if (exit_s == 127)
	{
		if (mode == 0)
			print_error_msg(cmd, "command not found", 0);
		else if (mode == 1)
			print_error_msg(cmd, "No such file or directory", 1);
	}
	else
	{
		if (mode == 1)
			print_error_msg(cmd, "Permission denied", 1);
		else if (mode == 0)
			print_error_msg(cmd, "Is a directory", 1);
	}
	shell->last_status_code = exit_s;
	shell->exec.cmd_exit_code = exit_s;
}

/**
 * print_file_err - Prints a file error message to standard error.
 * @filename: The filename related to the error.
 * @error: The error description string.
 * @exit_s: The exit status code to return.
 *
 * Prints the error message with the "bash: " prefix.
 *
 * Return: The provided exit status code.
 */
int	print_file_err(char *filename, char *error, int exit_s)
{
	print_error_msg(filename, error, 1);
	return (exit_s);
}
