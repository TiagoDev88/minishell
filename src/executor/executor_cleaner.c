/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 23:03:44 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/14 01:33:46 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_clean_child(t_shell *shell, int exit_s)
{
	if (shell->exec.files_container.lst)
		clean_files_s(&shell->exec.files_container.lst);
	if (shell->exec.pipe_lst)
		clean_pipe_s(&shell->exec.pipe_lst);
	if (shell->exec.procc_lst)
		clean_proccess_s(&shell->exec.procc_lst);
	exit(exit_s);
}

void	close_pipes(t_pipe **pipe_lst)
{
	t_pipe	*curr;

	curr = *pipe_lst;
	while (curr)
	{
		if (curr->write_fd != -1)
			close(curr->write_fd);
		if (curr->read_fd != -1)
			close(curr->read_fd);
		curr->write_fd = -1;
		curr->read_fd = -1;
		curr = curr->next;
	}
}

void	close_last_fds(t_exec *exec)
{
	if (exec->files_container.last_in_fd != STDIN_FILENO)
	{
		close(exec->files_container.last_in_fd);
		exec->files_container.last_in_fd = STDIN_FILENO;
	}
	if (exec->files_container.last_out_fd != STDOUT_FILENO)
	{
		close(exec->files_container.last_out_fd);
		exec->files_container.last_out_fd = STDOUT_FILENO;
	}
}

void	exit_clean(t_shell *shell, int exit_s)
{
	if (shell->envp && exit_s == 0)
		free_envp(&shell->envp);
	if (shell->tokens)
		free_tokens(&shell->tokens);
	if (shell->parser.cmd_lst)
		clean_cmds(&shell->parser, &shell->parser.cmd_lst, 0);
	if (shell->exec.files_container.lst)
		clean_files_s(&shell->exec.files_container.lst);
	if (shell->exec.pipe_lst)
		clean_pipe_s(&shell->exec.pipe_lst);
	if (shell->exec.procc_lst)
		clean_proccess_s(&shell->exec.procc_lst);
	if (exit_s >= 0)
	{
		if (shell->underscore)
			free(shell->underscore);
		if (exit_s == ENOMEM)
			print_error_msg(NULL, strerror(ENOMEM), 1);
		shell->last_status_code = exit_s;
		exit(exit_s);
	}
}

int	clean_mem(void *p1, void *p2, void *p3, int exit_s)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p3);
	return (exit_s);
}
