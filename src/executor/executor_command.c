/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:42:50 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/12 02:17:20 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect(int redir_type, t_shell *shell, int fd)
{
	if (redir_type == 1)
	{
		if (fd != STDIN_FILENO)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				print_error_msg(NULL, strerror(errno), 1);
				exit_clean(shell, errno);
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
				exit_clean(shell, errno);
			}
		}
	}
}

void	handle_redirects(t_shell *shell)
{
	if (shell->exec.files_container.last_in_fd >= 0)
		redirect(1, shell, shell->exec.files_container.last_in_fd);
	if (shell->exec.files_container.last_out_fd >= 0)
		redirect(2, shell, shell->exec.files_container.last_out_fd);
}

static void	exec_cmd(char *cmd_path, t_shell *shell, t_cmd *cmd, char **envp)
{
	validate_cmd(cmd_path, shell);
	execve(cmd_path, cmd->cmd_args, envp);
	print_error_msg(NULL, strerror(errno), 1);
	shell->last_status_code = errno;
	if (cmd_path && ft_strchr(cmd->cmd_args[0], '/'))
		free(cmd_path);
	exit_clean_child(shell, shell->last_status_code);
}

void	fork_proccess(t_shell *shell, t_exec *exec, t_cmd *cmd, char **envp)
{
	signal(SIGINT, sigint_handler);
	handle_redirects(shell);
	close_last_fds(exec);
	close_pipes(&exec->pipe_lst);
	if (ft_strchr(cmd->cmd_args[0], '/'))
		exec_cmd(cmd->cmd_args[0], shell, cmd, envp);
	else if (is_built_in(cmd->cmd_args[0]))
	{
		exec_built_in(shell, cmd, 0);
		exit_clean_child(shell, shell->last_status_code);
	}
	else
		exec_cmd(get_cmd_path(shell, cmd->cmd_args[0]), shell, cmd, envp);
	exit_clean_child(shell, shell->last_status_code);
}

void	execute_command(t_shell *shell, t_exec *exec, t_cmd *cmd, char **envp)
{
	t_proccess	*new;

	if (is_built_in(cmd->cmd_args[0]) && !shell->parser.n_pipes)
		exec_built_in(shell, cmd, 1);
	else
	{
		new = create_proccess();
		procc_add_back(&exec->procc_lst, new);
		signal(SIGINT, SIG_IGN);
		new->pid = fork();
		if (new->pid == -1)
		{
			print_error_msg(NULL, strerror(errno), 1);
			exit_clean(shell, EXIT_FAILURE);
		}
		else if (new->pid == 0)
			fork_proccess(shell, exec, cmd, envp);
	}
}
