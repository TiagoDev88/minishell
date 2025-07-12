/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:41:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/12 03:26:37 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_last_cmd_exit_code(t_shell *shell)
{
	t_proccess	*curr;
	int			status;
	int			sig;

	if (!shell->exec.procc_lst)
		return ;
	curr = shell->exec.procc_lst;
	close_last_fds(&shell->exec);
	close_pipes(&shell->exec.pipe_lst);
	while (curr)
	{
		waitpid(curr->pid, &status, 0);
		signal(SIGINT, sigint_handler);
		if (WIFEXITED(status))
			shell->last_status_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				ft_putstr_fd("\n", 1);
			shell->last_status_code = 128 + sig;
		}
		curr = curr->next;
	}
	if (shell->exec.file_exit_code)
		shell->last_status_code = shell->exec.file_exit_code;
}

int handle_cmds_redirs(t_exec *exec, t_cmd *cmd, t_token **token, t_shell *sh)
{
	t_token *tmp_token;

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

static void	exec_line(t_shell *shell, t_exec *exec, char **envp)
{
	t_token	*curr_token;
	t_cmd	*curr_cmd;

	curr_token = shell->tokens;
	curr_cmd = shell->parser.cmd_lst;
	while (curr_token)
	{
		if (!handle_cmds_redirs(exec, curr_cmd, &curr_token, shell))
			continue;
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

void	executor(t_shell *shell, char **envp)
{
	shell->exec.files_container.last_in_fd = 0;
	shell->exec.files_container.last_out_fd = 1;
	exec_line(shell, &shell->exec, envp);
	if (shell->exec.procc_lst)
		get_last_cmd_exit_code(shell);
	if (shell->exec.file_exit_code)
		shell->last_status_code = shell->exec.file_exit_code;
}
