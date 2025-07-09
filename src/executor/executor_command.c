/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:42:50 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/09 17:28:04 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static void	redirect(int redir_type, t_exec *exec, int fd)
{
	if (redir_type == 1)
	{
		if (fd != STDIN_FILENO)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				print_error_msg(NULL, strerror(errno), 1);
				exit_clean(exec, errno);
			}
		}
	}
	else
	{
		if (fd != STDOUT_FILENO)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				print_error_msg(NULL, strerror(errno), 1);
				exit_clean(exec, errno);
			}
		}
	}
}

static void	handle_redirects(t_exec *exec)
{
	if (exec->files_container.last_in_fd >= 0)
		redirect(1, exec, exec->files_container.last_in_fd);
	if (exec->files_container.last_out_fd >= 0)
		redirect(2, exec, exec->files_container.last_out_fd);
}

static void	exec_cmd(char *cmd_path, t_exec *exec, t_cmd *cmd_lst, char **envp)
{
	validate_cmd(cmd_path, exec);
	execve(cmd_path, cmd_lst->cmd_args, envp);
	print_error_msg(NULL, strerror(errno), 1);
	if (cmd_path)
		free(cmd_path);
	exit_clean(exec, errno);
}

void	execute_command(t_exec *exec, t_cmd **curr_cmd, char **envp)
{
	t_proccess	*new;
	t_cmd		*cmd;

	cmd = *curr_cmd;
	*curr_cmd = (*curr_cmd)->next;
	new = create_proccess();
	procc_add_back(&exec->procc_lst, new);
	signal(SIGINT, SIG_IGN);
	
	new->pid = fork();
	if (new->pid == -1)
	{
		print_error_msg(NULL, strerror(errno), 1);
		exit_clean(exec, EXIT_FAILURE);
	}
	else if (new->pid == 0)
	{
		signal(SIGINT, sigint_handler);
		handle_redirects(exec);
		close_last_fds(exec);
		close_pipes(&exec->pipe_lst);
		if (ft_strchr(cmd->cmd_args[0], '/'))
			exec_cmd(cmd->cmd_args[0], exec, cmd, envp);
		else
			exec_cmd(get_cmd_path(exec, cmd->cmd_args[0]), exec, cmd, envp);
	}
}
