/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:41:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/17 11:01:26 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * save_last_cmd_exit_code - Waits for a child process and saves its exit code.
 * @shell: Pointer to the shell structure containing execution context.
 * @proccess: Pointer to the process structure representing the child process.
 *
 * Waits for the specified child process to finish using waitpid.
 * If the process exited normally, stores its exit status 
 * in shell->last_status_code.
 * If terminated by a signal, stores 128 + signal number.
 * If the signal was SIGQUIT and the process is the last in the list,
 * prints "Quit (core dumped)" message followed by a newline.
 */
static void	save_last_cmd_exit_code(t_shell *shell, t_proccess *proccess)
{
	int			status;
	int			sig;

	if (proccess->pid == -1)
		return ;
	waitpid(proccess->pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_status_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (!proccess->next)
		{
			if (sig == SIGQUIT || sig == SIGINT)
			{
				if (sig == SIGQUIT)
					printf("Quit (core dumped)");
				printf("\n");
			}
		}
		shell->last_status_code = 128 + sig;
	}
}

/**
 * get_last_cmd_exit_code - Collects exit codes from all child processes.
 * @shell: Pointer to the shell structure containing execution context.
 *
 * Iterates through the list of child processes and calls
 * save_last_cmd_exit_code for each to update shell->last_status_code.
 * Also closes open file descriptors and pipes after execution.
 */
static void	get_last_cmd_exit_code(t_shell *shell)
{
	t_proccess	*curr_proccess;

	if (!shell->exec.procc_lst)
		return ;
	curr_proccess = shell->exec.procc_lst;
	close_last_fds(&shell->exec);
	close_pipes(&shell->exec.pipe_lst);
	while (curr_proccess)
	{
		save_last_cmd_exit_code(shell, curr_proccess);
		curr_proccess = curr_proccess->next;
	}
}

/**
 * handle_cmds_redirs - Handles commands and redirections for execution.
 * @exec: Pointer to the execution context.
 * @cmd: Pointer to the current command structure.
 * @token: Double pointer to the current token list.
 * @sh: Pointer to the shell structure.
 *
 * Checks for command presence and validates file redirections.
 * Updates execution flags regarding errors and command execution readiness.
 * Returns 0 if execution should not continue for current tokens, 1 otherwise.
 */
int	handle_cmds_redirs(t_exec *exec, t_cmd *cmd, t_token **token, t_shell *sh)
{
	t_token	*tmp_token;

	if (exec->file_exit_code && cmd)
		exec->file_exit_code = 0;
	if (has_cmd(token))
		exec->exec_h.exec_cmd = 1;
	if (*token)
		if (!validate_and_open_files(token, sh))
			exec->exec_h.err_file = 1;
	tmp_token = *token;
	if (has_cmd(token) && exec->exec_h.exec_cmd == 0)
	{
		*token = tmp_token;
		return (0);
	}
	return (1);
}

/**
 * exec_line - Executes the parsed command line.
 * @shell: Pointer to the shell structure containing all context.
 * @exec: Pointer to the execution context.
 * @envp: Environment variables array.
 *
 * Iterates over tokens and commands, handling redirections, pipes,
 * and command execution. Manages file descriptor state and cleans
 * temporary resources after each command.
 */
static void	exec_line(t_shell *shell, t_exec *exec, char **envp)
{
	t_token	*curr_token;
	t_cmd	*curr_cmd;

	curr_token = shell->tokens;
	curr_cmd = shell->parser.cmd_lst;
	while (curr_token)
	{
		if (!handle_cmds_redirs(exec, curr_cmd, &curr_token, shell))
			continue ;
		if (curr_token && curr_token->type == TOKEN_PIPE)
			exec->exec_h.last_pipe = handle_pipe(shell, &curr_token);
		if (!exec->exec_h.err_file && exec->exec_h.exec_cmd && curr_cmd)
			execute_command(shell, exec, curr_cmd, envp);
		else if (exec->exec_h.err_file && exec->exec_h.exec_cmd)
			exec->file_exit_code = 1;
		if (exec->exec_h.last_pipe)
			exec->files_container.last_in_fd = exec->exec_h.last_pipe->read_fd;
		ft_memset(&exec->exec_h, 0, sizeof(t_exec_helper));
		clean_files_s(&exec->files_container.lst);
		exec->files_container.last_out_fd = 1;
		if (curr_cmd)
			curr_cmd = curr_cmd->next;
	}
}

/**
 * executor - Main function to handle the execution phase of the shell.
 * @shell: Pointer to the main shell structure containing 
 * all execution context.
 * @envp: Environment variables passed to execve.
 *
 * This function:
 * - Initializes I/O defaults (stdin and stdout).
 * - Iterates through the token and command lists, dispatching execution logic.
 * - Handles redirections, file opening errors, and command execution.
 * - Tracks child process exit statuses and 
 * updates the shell’s last status code.
 * Logic flow:
 * - Calls exec_line() to iterate through the parsed command list and tokens.
 * - Waits for child processes and captures their exit codes.
 * - Updates shell->last_status_code based on:
 *    - Command execution result
 *    - File redirection failure
 *
 * Return: void
 */

void	executor(t_shell *shell, char **envp)
{
	shell->exec.files_container.last_in_fd = 0;
	shell->exec.files_container.last_out_fd = 1;
	exec_line(shell, &shell->exec, envp);
	if (shell->exec.procc_lst)
		get_last_cmd_exit_code(shell);
	if (shell->exec.cmd_exit_code)
		shell->last_status_code = shell->exec.cmd_exit_code;
	if (shell->exec.file_exit_code)
		shell->last_status_code = shell->exec.file_exit_code;
	shell->exec.cmd_exit_code = 0;
	shell->exec.file_exit_code = 0;
	signal(SIGINT, sigint_handler);
}
