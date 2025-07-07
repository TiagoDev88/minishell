/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:41:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/07 12:43:05 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_last_cmd_exit_code(t_exec *exec)
{
	t_proccess	*curr;
	int			exit_code;
	int			status;

	exit_code = 0;
	if (!exec->procc_lst)
		return ;
	curr = exec->procc_lst;
	clean_files_s(&exec->files_container.lst);
	clean_pipe_s(&exec->pipe_lst);
	while (curr)
	{
		waitpid(curr->pid, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		curr = curr->next;
	}
	clean_proccess_s(&exec->procc_lst);
	g_exit_status = exit_code;
}

static void	exec_line(t_token *tokens, t_cmd *cmds, t_exec *exec, char **envp)
{
	t_token	*curr_token;
	t_cmd	*curr_cmd;

	curr_token = tokens;
	curr_cmd = cmds;
	while (curr_token)
	{
		if (has_cmd(&curr_token))
			exec->exec_h.exec_cmd = 1;
		if (curr_token)
			if (!validate_and_open_files(&curr_token, exec))
				exec->exec_h.err_file = 1;
		if (has_cmd(&curr_token))
			exec->exec_h.exec_cmd = 1;
		if (curr_token && curr_token->type == TOKEN_PIPE)
			exec->exec_h.last_pipe = handle_pipe(exec, &curr_token);
		if (!exec->exec_h.err_file && exec->exec_h.exec_cmd && curr_cmd)
			execute_command(exec, &curr_cmd, envp);
		if (exec->exec_h.last_pipe)
			exec->files_container.last_in_fd = exec->exec_h.last_pipe->read_fd;
		ft_memset(&exec->exec_h, 0, sizeof(t_exec_helper));
		clean_files_s(&exec->files_container.lst);
		exec->files_container.last_out_fd = 1;
	}
}

void	executor(t_token *tokens, t_cmd *cmd_lst, char **envp)
{
	t_exec	exec;

	ft_memset(&exec, 0, sizeof(t_exec));
	exec.files_container.last_in_fd = 0;
	exec.files_container.last_out_fd = 1;
	exec_line(tokens, cmd_lst, &exec, envp);
	if (cmd_lst)
		get_last_cmd_exit_code(&exec);
	printf("EXIT_CODE = %i\n", g_exit_status);
}
