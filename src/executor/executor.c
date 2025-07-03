/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:41:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/03 11:47:31 by edfreder         ###   ########.fr       */
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

void get_last_cmd_exit_code(t_exec *exec)
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
void	close_pipes(t_pipe **pipe_lst)
{
	t_pipe	*curr;

	curr = *pipe_lst;
	while (curr)
	{
		close(curr->write_fd);
		close(curr->read_fd);
		curr = curr->next;
	}
}

void	close_last_fds(t_exec *exec)
{
	if (exec->files_container.last_in_fd > 2)
	{
		close(exec->files_container.last_in_fd);
		exec->files_container.last_in_fd = 0;
	}
	if (exec->files_container.last_out_fd > 2)
	{
		close(exec->files_container.last_out_fd);
		exec->files_container.last_out_fd = 1;
	}
}

void	exec_pid_father(t_exec *exec)
{
	close_last_fds(exec);
	// Limpar estrutura
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
		close_last_fds(exec);
		if (ft_strchr(cmd->cmd_args[0], '/'))
			exec_cmd(cmd->cmd_args[0], exec, cmd, envp);
		else
			exec_cmd(get_cmd_path(exec, cmd->cmd_args[0]), exec, cmd, envp);
	}
	else
		exec_pid_father(exec);
}

/*
void	execute_simple(t_token *tokens, t_cmd *cmd_lst, t_exec *exec, char **envp)
{
	t_token *curr_token;

 	curr_token = tokens;
 	while (curr_token && curr_token->type == TOKEN_WORD)
 		curr_token = curr_token->next;
 	if (curr_token)
 		if (!open_files(&curr_token, exec))
 			return ;
 	if (!cmd_lst)
 		return ;
 	// Confirmar se sao comandos built-in
 		// Se forem chamar funcoes
 		// Se nao abrir forks e executar.
 	exec_pid_son(exec, cmd_lst, envp);
 	exec_pid_father(exec);
}
*/

int	has_cmd(t_token **curr)
{
	t_token	*tmp;

	tmp = *curr;
	while (*curr && (*curr)->type == TOKEN_WORD)
		*curr = (*curr)->next;
	if (tmp != *curr)
		return (1);
	return (0);
}

t_pipe *save_pipe(t_exec *exec, t_files_container *files_container)
{
	int		pipe_fds[2];
	t_pipe	*new_pipe;

	new_pipe = malloc(sizeof(t_pipe));
	if (!new_pipe)
	{
		print_error_msg(NULL, "malloc: error", 1);
		exit_clean(exec, 2);
	}
	if (pipe(pipe_fds) == -1)
	{
		printf("oi\n");
		return (NULL);
	}
	new_pipe->write_fd = pipe_fds[1];
	printf("pipe fd 1: %i\n", pipe_fds[1]);
	new_pipe->read_fd = pipe_fds[0];
	new_pipe->next = NULL;
	return (new_pipe);
}

void	execute_simple(t_token *tokens, t_cmd *cmd_lst, t_exec *exec, char **envp)
{
	t_token *curr_token;
	t_cmd	*curr_cmd;
	int		exec_cmd;
	int		err_file;
	t_pipe	*last_pipe;

	curr_token = tokens;
	curr_cmd = cmd_lst;
	while (curr_token)
	{
		printf("TOKEN_VALUE: %s\n", curr_token->value);
		last_pipe = NULL;
		exec_cmd = 0;
		err_file = 0;
		// Passar as palavras iniciais
		if (has_cmd(&curr_token))
			exec_cmd = 1;
		// Passar os ficheiros.
		if (curr_token)
			if (!open_files(&curr_token, exec))
				err_file = 1;
		// Passar possiveis flags ou proprio comando.
		if (has_cmd(&curr_token))
			exec_cmd = 1;
		if (curr_token && curr_token->type == TOKEN_PIPE)
		{
			// save pipe.
			last_pipe = save_pipe(exec, &exec->files_container);
			exec->files_container.last_out_fd = last_pipe->write_fd;
			curr_token = curr_token->next;
		}
		printf("last_in: %i last_out: %i\n", exec->files_container.last_in_fd, exec->files_container.last_out_fd);
		if (!err_file && exec_cmd && curr_cmd)
		{
			exec_pid_son(exec, curr_cmd, envp);
			curr_cmd = curr_cmd->next;
		}
		else
			close_files(&exec->files_container);
		if (last_pipe)
		{
			printf("Last pipe: %i %i\n", last_pipe->read_fd, last_pipe->write_fd);
			exec->files_container.last_in_fd = last_pipe->read_fd;
		}
		printf("last_in: %i last_out: %i\n", exec->files_container.last_in_fd, exec->files_container.last_out_fd);
		//clean_files(&exec->files_container.lst);
	}
	if (cmd_lst)
		get_last_cmd_exit_code(exec);
}

void	execute(t_token *tokens, t_cmd *cmd_lst, char **envp)
{
	t_exec exec;

	ft_memset(&exec, 0, sizeof(t_exec));
	exec.files_container.last_in_fd = 0;
	exec.files_container.last_out_fd = 1;
	execute_simple(tokens, cmd_lst, &exec, envp);
	//printf("Is a pipeline\n");
	printf("EXIT_CODE = %i\n", EXIT_STATUS);
}

/*

TODO: Erros, leaks, fecho de ficheiros, organizar codigo.

*/