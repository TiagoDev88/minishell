/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:06:44 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/02 00:58:50 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error_msg(char *arg, char *error, int mode)
{
	if (mode == 1)
		ft_putstr_fd("bash: ", 2);
	if (arg)
			ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	if (error)
		ft_putendl_fd(error, 2);
}

void print_cmd_err_and_exit(char *cmd, int mode, int exit_status, t_exec *exec)
{
	if (exit_status == 127)
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
	exit_clean(exec, exit_status);
}

int print_file_err_and_return(char *filename, char *error, int exit_status)
{
	print_error_msg(filename, error, 1);
	return (exit_status);
}