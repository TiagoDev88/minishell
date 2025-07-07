/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:16:31 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/07 01:05:27 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_pipe_s(t_pipe **pipe_lst)
{
	t_pipe	*curr;
	t_pipe	*tmp;

	if (!pipe_lst || !(*pipe_lst))
		return ;
	curr = *pipe_lst;
	while (curr)
	{
		tmp = curr->next;
		if (curr->read_fd != -1)
			close(curr->read_fd);
		if (curr->write_fd != -1)
			close(curr->write_fd);
		free(curr);
		curr = tmp;
	}
	*pipe_lst = NULL;
}

static void	add_pipe_back(t_pipe **pipe_lst, t_pipe *new)
{
	t_pipe	*curr;

	if (!(*pipe_lst))
		*pipe_lst = new;
	else
	{
		curr = *pipe_lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

static t_pipe *save_pipe(t_exec *exec)
{
	int		pipe_fds[2];
	t_pipe	*new_pipe;

	new_pipe = malloc(sizeof(t_pipe));
	if (!new_pipe)
	{
		print_error_msg(NULL, strerror(errno), 1);
		exit_clean(exec, errno);
	}
	new_pipe->next = NULL;
	add_pipe_back(&exec->pipe_lst, new_pipe);
	if (pipe(pipe_fds) == -1)
	{
		print_error_msg(NULL, strerror(errno), 1);
		exit_clean(exec, errno);
	}
	new_pipe->write_fd = pipe_fds[1];
	new_pipe->read_fd = pipe_fds[0];
	return (new_pipe);
}

t_pipe	*handle_pipe(t_exec *exec, t_token **curr_token)
{
	t_pipe	*last_pipe;

	last_pipe = save_pipe(exec);
	if (exec->files_container.last_out_fd == 1)
		exec->files_container.last_out_fd = last_pipe->write_fd;
	*curr_token = (*curr_token)->next;
	return (last_pipe);
}
