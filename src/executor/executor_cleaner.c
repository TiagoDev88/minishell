/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 23:03:44 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/07 01:08:12 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exit_clean(t_exec *exec, int exit_status)
{
	if (exec->files_container.lst)
		clean_files_s(&exec->files_container.lst);
	if (exec->pipe_lst)
		clean_pipe_s(&exec->pipe_lst);
	if (exec->procc_lst)
		clean_proccess_s(&exec->procc_lst);
	EXIT_STATUS = exit_status;
	exit(exit_status);
}

int clean_mem(void *p1, void *p2, void *p3, int exit_status)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p3);
	return (exit_status);
}