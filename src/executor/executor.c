/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:41:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/05 01:45:02 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int EXIT_STATUS = 0;

void	execute_line(t_token *tokens, t_cmd *cmd_lst, t_exec *exec, char **envp)
{
	t_token *curr_token;
	t_cmd	*curr_cmd;

	curr_token = tokens;
	curr_cmd = cmd_lst;
	while (curr_token)
	{
		if (has_cmd(&curr_token))
			exec->exec_helper.exec_cmd = 1;
		if (curr_token)
			if (!validate_and_open_files(&curr_token, exec))
				exec->exec_helper.err_file = 1;
		if (has_cmd(&curr_token))
			exec->exec_helper.exec_cmd = 1;
		if (curr_token && curr_token->type == TOKEN_PIPE)
			exec->exec_helper.last_pipe = handle_pipe(exec, &curr_token);
		if (!exec->exec_helper.err_file && exec->exec_helper.exec_cmd && curr_cmd)
			execute_command(exec, &curr_cmd, envp);
		if (exec->exec_helper.last_pipe)
			exec->files_container.last_in_fd = exec->exec_helper.last_pipe->read_fd;
		ft_memset(&exec->exec_helper, 0, sizeof(t_exec_helper));
		clean_files(&exec->files_container.lst);
		exec->files_container.last_out_fd = 1;
	}
}

void	executor(t_token *tokens, t_cmd *cmd_lst, char **envp)
{
	t_exec exec;

	ft_memset(&exec, 0, sizeof(t_exec));
	exec.files_container.last_in_fd = 0;
	exec.files_container.last_out_fd = 1;
	execute_line(tokens, cmd_lst, &exec, envp);
	if (cmd_lst)
		get_last_cmd_exit_code(&exec);
	printf("EXIT_CODE = %i\n", EXIT_STATUS);
}
