/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:06:44 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/14 01:47:35 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	file_has_error(t_shell *shell, t_token **curr_token, int exit_status)
{
	shell->last_status_code = 1;
	print_file_err((*curr_token)->next->value, strerror(exit_status), 0);
	while (*curr_token && is_redirect(*curr_token))
	{
		*curr_token = (*curr_token)->next->next;
		if (*curr_token && (*curr_token)->type == TOKEN_WORD
			&& ((*curr_token)->next && is_redirect((*curr_token)->next)))
			*curr_token = (*curr_token)->next;
	}
	return (0);
}

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

int	print_file_err(char *filename, char *error, int exit_s)
{
	print_error_msg(filename, error, 1);
	return (exit_s);
}
