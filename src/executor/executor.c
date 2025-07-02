/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:41:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/02 14:58:34 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int EXIT_STATUS = 0;

/*
void	execute_pipeline(t_token *tokens, t_cmd *cmd_list, char **envp)
{
	(void)tokens;
	(void)cmd_lst;
	(void)envp;
	return ;
}
*/

void 	procc_add_back(t_proccess **procc_lst, t_proccess *new_proccess)
{
	t_proccess	*curr;
	
	if (!(*procc_lst))
		*procc_lst = new_proccess;
	else
	{
		curr = *procc_lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new_proccess;
	}
}

pid_t	*create_pid(t_proccess **procc_lst)
{
	t_proccess *new_proccess;

	new_proccess = malloc(sizeof(t_proccess));
	if (!new_proccess)
		return (NULL);
	new_proccess->next = NULL;
	procc_add_back(procc_lst, new_proccess);
	return (&new_proccess->pid);
}

void exec_pid_father(t_exec *exec)
{
	t_proccess	*curr;
	int			exit_code;
	int			status;

	exit_code = 0;
	if (!exec->procc_lst)
		return ;
	curr = exec->procc_lst;
	while (curr)
	{
		waitpid(curr->pid, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		curr = curr->next;
	}
	EXIT_STATUS = exit_code;
}

void	exec_pid_son(t_exec *exec, t_cmd *cmd, char **envp)
{
	pid_t *curr_pid;

	curr_pid = create_pid(&exec->procc_lst);
	if (!curr_pid)
		return ;
	*curr_pid = fork();
	if (*curr_pid == -1)
		exit_clean(exec, EXIT_FAILURE);
	else if (*curr_pid == 0)
	{
		handle_redirects(exec);
		close_files(&exec->files_container);
		if (ft_strchr(cmd->cmd_args[0], '/'))
			exec_cmd(cmd->cmd_args[0], exec, cmd, envp);
		else
			exec_cmd(get_cmd_path(exec, cmd->cmd_args[0]), exec, cmd, envp);
	}
}

void	execute_simple(t_token *tokens, t_cmd *cmd_lst, t_exec *exec, char **envp)
{
	t_token *curr_token;

	curr_token = tokens;
	while (curr_token && curr_token->type == TOKEN_WORD)
		curr_token = curr_token->next;
	if (curr_token)
		if (!open_files(&curr_token, exec))
			return ;
	t_file *curr = exec->files_container.lst;
	while (curr)
	{
		printf("%i %s %i\n", curr->fd, curr->filename, curr->unlink);
		curr = curr->next;
	}
	if (!cmd_lst)
		return ;
	// Confirmar se sao comandos built-in
		// Se forem chamar funcoes
		// Se nao abrir forks e executar.
	exec_pid_son(exec, cmd_lst, envp);
	exec_pid_father(exec);
}

void	execute(t_token *tokens, t_cmd *cmd_lst, char **envp)
{
	t_exec exec;

	ft_memset(&exec, 0, sizeof(t_exec));
	exec.files_container.last_in_fd = -2;
	exec.files_container.last_out_fd = -2;
	if (!cmd_lst || (cmd_lst && !cmd_lst->next))
		execute_simple(tokens, cmd_lst, &exec, envp);
	else
		printf("Is a pipeline\n");
	printf("EXIT_CODE = %i\n", EXIT_STATUS);
	clean_files(&exec.files_container.lst);
}