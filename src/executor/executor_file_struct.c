/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_file_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:51:27 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/22 15:05:46 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * clean_files_s - Frees and closes all file nodes in the linked list.
 * @file_lst: Pointer to the head of the t_file linked list.
 *
 * Closes file descriptors > 2, unlinks temporary files marked for unlink,
 * frees filenames and nodes, and sets the head pointer to NULL.
 */
void	clean_files_s(t_file **file_lst)
{
	t_file	*curr;
	t_file	*tmp;

	if (file_lst)
	{
		curr = *file_lst;
		while (curr)
		{
			tmp = curr->next;
			if (curr->fd > 2)
				close(curr->fd);
			if (curr->unlink)
				unlink(curr->filename);
			free(curr->filename);
			free(curr);
			curr = tmp;
		}
		*file_lst = NULL;
	}
}

/**
 * add_file_back - Adds a new file node to the end of the file list.
 * @file_lst: Pointer to the head of the t_file linked list.
 * @new_file: Pointer to the new file node to add.
 *
 * If the list is empty, sets new_file as the head.
 * Otherwise, traverses the list and appends new_file at the end.
 */
void	add_file_back(t_file **file_lst, t_file *new_file)
{
	t_file	*curr;

	if (!(*file_lst))
		*file_lst = new_file;
	else
	{
		curr = *file_lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new_file;
	}
}

/**
 * create_file_node - Allocates and initializes a new file node.
 *
 * Initializes fd to -1, unlink flag to 0, filename and next to NULL.
 *
 * Return: Pointer to the new file node or NULL if malloc fails.
 */

t_file	*create_file_node(void)
{
	t_file	*new_file;

	new_file = malloc(sizeof(t_file));
	if (!new_file)
		return (NULL);
	new_file->fd = -1;
	new_file->unlink = 0;
	new_file->filename = NULL;
	new_file->next = NULL;
	return (new_file);
}

/**
 * add_file - Creates and adds a file node representing a redirection.
 * @f_con: Pointer to the files container managing open files.
 * @filename: The filename associated with the redirection.
 * @redir: The redirection token type (e.g., TOKEN_REDIR_IN).
 * @sh: Pointer to the shell struct (for error handling/status).
 *
 * Opens the file according to the redirection type:
 * - TOKEN_REDIR_IN: open for reading
 * - TOKEN_HEREDOC: handle heredoc input and file creation
 * - TOKEN_REDIR_OUT: open for writing (truncate)
 * - TOKEN_APPEND: open for appending
 *
 * Updates the last_in_fd or last_out_fd in f_con accordingly.
 * Adds the new file node to the files list.
 *
 * Return: 0 on success, -1 on failure.
 */
int	add_file(t_files_container *f_con, char *filename, int redir, t_shell *sh)
{
	t_file	*new_file;

	new_file = create_file_node();
	add_file_back(&f_con->lst, new_file);
	if (redir == TOKEN_REDIR_IN)
		new_file->fd = open(filename, O_RDONLY);
	else if (redir == TOKEN_HEREDOC)
		return (heredoc(&new_file, filename, &f_con));
	else if (redir == TOKEN_REDIR_OUT)
		new_file->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir == TOKEN_APPEND)
		new_file->fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (new_file->fd == -1)
		return (errno);
	if (redir == TOKEN_REDIR_IN || redir == TOKEN_HEREDOC)
		f_con->last_in_fd = new_file->fd;
	else
		f_con->last_out_fd = new_file->fd;
	new_file->filename = ft_strdup(filename);
	if (!new_file->filename)
		return (-1);
	sh->last_status_code = 0;
	return (0);
}
