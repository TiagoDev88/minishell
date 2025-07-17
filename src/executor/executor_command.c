/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:42:50 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/17 13:56:29 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * redirect - Redirects standard input or output to a given file descriptor.
 * @redir_type: 1 for stdin redirection, 2 for stdout redirection.
 * @shell: Pointer to the shell struct for error handling.
 * @fd: The file descriptor to redirect from.
 *
 * Uses dup2 to replace stdin or stdout with fd, exiting on failure.
 */
static void	redirect(int redir_type, t_shell *shell, int fd)
{
	if (redir_type == 1)
	{
		if (fd != STDIN_FILENO)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				print_error_msg(NULL, strerror(errno), 1);
				exit_clean(shell, errno, 0);
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
				exit_clean(shell, errno, 0);
			}
		}
	}
}

/**
 * handle_redirects - Applies input/output redirections for the current command.
 * @shell: Pointer to the shell struct which contains file descriptors.
 *
 * Redirects stdin and stdout to the last input/output fds
 * stored in files_container.
 */
void	handle_redirects(t_shell *shell)
{
	if (shell->exec.files_container.last_in_fd >= 0)
		redirect(1, shell, shell->exec.files_container.last_in_fd);
	if (shell->exec.files_container.last_out_fd >= 0)
		redirect(2, shell, shell->exec.files_container.last_out_fd);
}

/**
 * exec_cmd - Executes the command using execve.
 * @cmd_path: Full path to the executable.
 * @shell: Pointer to the shell struct for error handling.
 * @cmd: The command structure with arguments.
 * @envp: Environment variables array.
 *
 * If execve fails, prints error, updates status and exits child process.
 */
static void	exec_cmd(char *cmd_path, t_shell *shell, t_cmd *cmd, char **envp)
{
	execve(cmd_path, cmd->cmd_args, envp);
	printf("Execve error\n");
	print_error_msg(NULL, strerror(errno), 1);
	shell->last_status_code = errno;
	if (cmd_path && ft_strchr(cmd->cmd_args[0], '/'))
		free(cmd_path);
	exit_clean_child(shell, shell->last_status_code);
}

/**
 * fork_proccess - Child process routine after fork.
 * @shell: Pointer to the shell struct.
 * @exec: Execution context containing pipes and processes.
 * @cmd: Command to execute.
 * @envp: Environment variables array.
 *
 * Sets signal handlers, handles redirections, closes unused fds,
 * then executes the command or builtin. Exits on completion.
 */
void	fork_proccess(t_shell *shell, t_exec *exec, t_cmd *cmd, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_redirects(shell);
	close_last_fds(exec);
	close_pipes(&exec->pipe_lst);
	if (ft_strchr(cmd->cmd_args[0], '/'))
		exec_cmd(cmd->cmd_path, shell, cmd, envp);
	else if (is_built_in(cmd->cmd_args[0]))
		exec_built_in(shell, cmd);
	else
		exec_cmd(cmd->cmd_path, shell, cmd, envp);
	exit_clean(shell, shell->last_status_code, 0);
}

/**
 * execute_command - Launches execution of a command, forking if needed.
 * @shell: Pointer to the shell struct.
 * @exec: Execution context.
 * @cmd: Command structure containing args and paths.
 * @envp: Environment variables array.
 *
 * Executes builtins directly if no pipes. Otherwise forks child process,
 * setting up process list and signal handlers.
 */
void	execute_command(t_shell *shell, t_exec *exec, t_cmd *cmd, char **envp)
{
	t_proccess	*new;

	if (is_built_in(cmd->cmd_args[0]) && !shell->parser.n_pipes)
		exec_built_in(shell, cmd);
	else
	{
		if (!is_valid_cmd(shell, cmd))
			return ;
		else
			update_last_cmd_env(shell, get_envp_node("_", shell->envp), cmd);
		new = create_proccess();
		if (!new)
			return ;
		procc_add_back(&exec->procc_lst, new);
		signal(SIGINT, SIG_IGN);
		new->pid = fork();
		if (new->pid == -1)
		{
			print_error_msg(NULL, strerror(errno), 1);
			exit_clean(shell, EXIT_FAILURE, 1);
		}
		else if (new->pid == 0)
			fork_proccess(shell, exec, cmd, envp);
	}
}
