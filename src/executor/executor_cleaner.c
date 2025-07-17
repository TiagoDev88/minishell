/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 23:03:44 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/17 13:50:59 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * exit_clean_child - Frees all resources used in child process and exits.
 * @shell: Pointer to shell context holding resources.
 * @exit_s: Exit status code for the child process.
 *
 * Frees file lists, pipes, and process lists before exiting with exit_s.
 * This is used in child after fork to prevent leaks.
 */
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

/**
 * close_pipes - Closes all pipe file descriptors in the list.
 * @pipe_lst: Pointer to the head of the pipe list.
 *
 * Iterates through pipes and closes read and write ends if open.
 * Sets file descriptors to -1 after closing to avoid reuse.
 */
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

/**
 * close_last_fds - Closes the last used input/output file descriptors.
 * @exec: Pointer to execution context containing file descriptors.
 *
 * Closes last_in_fd and last_out_fd if they are not standard input/output,
 * then resets them to STDIN_FILENO and STDOUT_FILENO.
 */
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

/**
 * exit_clean - Frees all shell resources and exits the shell.
 * @shell: Pointer to shell context holding all resources.
 * @exit_s: Exit status code; if negative, does not exit.
 *
 * Frees environment, tokens, commands, files, pipes, and processes.
 * Prints an error message if exiting due to ENOMEM.
 * Frees the underscore variable if present.
 */
void	exit_clean(t_shell *shell, int exit_s, int is_exit)
{
	if (shell->envp && exit_s >= 0)
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
		if (is_exit)
			rl_clear_history();
		exit(exit_s);
	}
}

/**
 * clean_mem - Helper to free up to three pointers and return exit code.
 * @p1: Pointer to free, or NULL.
 * @p2: Pointer to free, or NULL.
 * @p3: Pointer to free, or NULL.
 * @exit_s: Exit status code to return.
 *
 * Frees each pointer if non-NULL, then returns exit_s.
 * Useful for error cleanup.
 */
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
