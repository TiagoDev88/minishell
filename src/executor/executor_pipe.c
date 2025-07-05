/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:16:31 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/05 01:13:39 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_pipe *save_pipe(t_exec *exec, t_files_container *files_container)
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
		print_error_msg(NULL, strerror(errno), 1);
		exit_clean(exec, errno);
	}
	new_pipe->write_fd = pipe_fds[1];
	new_pipe->read_fd = pipe_fds[0];
	new_pipe->next = NULL;
	add_pipe_back(&exec->pipe_lst, new_pipe);
	return (new_pipe);
}

t_pipe	*handle_pipe(t_exec *exec, t_token **curr_token)
{
	t_pipe	*last_pipe;

	last_pipe = save_pipe(exec, &exec->files_container);
	if (exec->files_container.last_out_fd == 1)
		exec->files_container.last_out_fd = last_pipe->write_fd;
	*curr_token = (*curr_token)->next;
	return (last_pipe);
}
