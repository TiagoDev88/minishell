/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:42:50 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/10 14:47:46 by edfreder         ###   ########.fr       */
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

static void	handle_redirects(t_shell *shell)
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
	if (cmd_path && ft_strchr(cmd->cmd_args[0], '/'))
		free(cmd_path);
	exit_clean(shell, errno);
}

int	exec_built_in(t_shell *shell, t_cmd *curr_cmd)
{
	if (!ft_strcmp(curr_cmd->cmd_args[0], "cd"))
		g_exit_status = ft_cd(curr_cmd, &shell->envp, shell);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "echo"))
		g_exit_status = ft_echo(curr_cmd);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "env"))
		g_exit_status = ft_env(curr_cmd, shell->envp);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "exit"))
		ft_exit(&shell->parser.cmd_lst);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "export"))
		g_exit_status = ft_export(curr_cmd, &shell->envp);
	/*
	else if (ft_strcmp(curr_cmd->cmd_args[0], "pwd"))
		ft_
	else if (ft_strcmp(curr_cmd->cmd_args[0], "unset"))
		ft_echo(curr_cmd);
	*/
	else
		return (0);
	return (1);
}

void	execute_command(t_shell *shell, t_exec *exec, t_cmd **curr_cmd, char **envp)
{
	t_proccess	*new;
	t_cmd		*cmd;

	cmd = *curr_cmd;
	*curr_cmd = (*curr_cmd)->next;
	if (!exec_built_in(shell, cmd))
	{
		new = create_proccess();
		procc_add_back(&exec->procc_lst, new);
		printf("Fork\n");
		signal(SIGINT, SIG_IGN);
		new->pid = fork();
		if (new->pid == -1)
		{
			print_error_msg(NULL, strerror(errno), 1);
			exit_clean(shell, EXIT_FAILURE);
		}
		else if (new->pid == 0)
		{
			signal(SIGINT, sigint_handler);
			handle_redirects(shell);
			close_last_fds(exec);
			close_pipes(&exec->pipe_lst);
			if (ft_strchr(cmd->cmd_args[0], '/'))
				exec_cmd(cmd->cmd_args[0], shell, cmd, envp);
			else
				exec_cmd(get_cmd_path(shell, cmd->cmd_args[0]), shell, cmd, envp);
		}
	}
}
