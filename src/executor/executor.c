/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:41:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/30 09:02:32 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



/*
void	execute_pipeline(t_token *tokens, t_cmd *cmd_list, char **envp)
{
	(void)tokens;
	(void)cmd_lst;
	(void)envp;
	return ;
}
*/

void	execute_simple(t_token *tokens, t_cmd *cmd_lst, t_exec *exec, char **envp)
{
	t_token *curr_token;
	pid_t	pid;

	curr_token = tokens;
	while (curr_token && curr_token->type == TOKEN_WORD)
		curr_token = curr_token->next;
	if (curr_token)
		if (!open_files(&curr_token, &exec->files_container))
			return ;
	if (!cmd_lst)
		return ;
	pid = fork();
	if (pid == -1)
		exit_clean(exec, "fork", EXIT_FAILURE);
	else if (pid == 0)
	{
		handle_redirects(&exec->files_container);
		close_files(&exec->files_container);
		if (cmd_lst->cmd_args[0][0] == '/')
			exec_cmd(cmd_lst->cmd_args[0], exec, envp);
		else
			exec_cmd(get_cmd_path(cmd_lst->cmd_args[0]), exec, envp);
	}
	else
		wait(NULL); // Guardar exit code.
}

void	execute(t_token *tokens, t_cmd *cmd_lst, char **envp)
{
	t_exec exec;

	ft_memset(&exec, 0, sizeof(t_exec));
	if (!cmd_lst || (cmd_lst && !cmd_lst->next))
		execute_simple(tokens, cmd_lst, &exec, envp);
	else
		printf("Is a pipeline\n");
	//get_cmd_path("ls");
}