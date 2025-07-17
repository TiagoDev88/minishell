/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:16:31 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/17 13:58:08 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * clean_pipe_s - Frees and closes all pipes in the pipe list.
 * @pipe_lst: Pointer to the head of the t_pipe linked list.
 *
 * Iterates through the pipe list, closes read and write file descriptors
 * if they are open, frees the nodes, and sets the list pointer to NULL.
 */
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

/**
 * add_pipe_back - Adds a new pipe node at the end of the pipe list.
 * @pipe_lst: Pointer to the head of the t_pipe linked list.
 * @new: New pipe node to add.
 *
 * Adds the new node to the end of the list or sets it as head if list is empty.
 * 
 * Note: This function is static and used internally.
 */
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

/**
 * save_pipe - Creates a new pipe node, initializes it, 
 * and adds it to the shell's pipe list.
 * @shell: Pointer to the main shell structure.
 *
 * Allocates memory for a new t_pipe, 
 * creates a new pipe using pipe(2) system call,
 * stores the read and write file descriptors, 
 * and appends it to the shell's pipe list.
 * On failure, prints an error and exits cleanly.
 *
 * Return: Pointer to the newly created t_pipe node.
 * 
 * Note: This function is static and used internally.
 */
static t_pipe	*save_pipe(t_shell *shell)
{
	int		pipe_fds[2];
	t_pipe	*new_pipe;

	new_pipe = malloc(sizeof(t_pipe));
	if (!new_pipe)
	{
		print_error_msg(NULL, strerror(ENOMEM), 1);
		exit_clean(shell, ENOMEM, 1);
	}
	new_pipe->next = NULL;
	add_pipe_back(&shell->exec.pipe_lst, new_pipe);
	if (pipe(pipe_fds) == -1)
	{
		print_error_msg(NULL, strerror(errno), 1);
		exit_clean(shell, errno, 1);
	}
	new_pipe->write_fd = pipe_fds[1];
	new_pipe->read_fd = pipe_fds[0];
	return (new_pipe);
}

/**
 * handle_pipe - Handles a pipe token by creating and saving a pipe node.
 * @shell: Pointer to the main shell structure.
 * @curr_token: Pointer to the current token pointer, 
 * expected to be at a pipe token.
 *
 * Calls save_pipe to create a pipe node, updates shell's file descriptors for
 * last output, advances the token pointer past the pipe token, and returns
 * the new pipe node.
 *
 * Return: Pointer to the created t_pipe node.
 */
t_pipe	*handle_pipe(t_shell *shell, t_token **curr_token)
{
	t_pipe	*last_pipe;

	last_pipe = save_pipe(shell);
	if (shell->exec.files_container.last_out_fd == 1)
		shell->exec.files_container.last_out_fd = last_pipe->write_fd;
	*curr_token = (*curr_token)->next;
	return (last_pipe);
}
