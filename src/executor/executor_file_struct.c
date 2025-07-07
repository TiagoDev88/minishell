/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_file_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:51:27 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/07 19:34:21 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	add_file(t_files_container *f_con, char *filename, int redir_type)
{
	t_file	*new_file;

	new_file = create_file_node();
	if (redir_type == TOKEN_REDIR_IN)
		new_file->fd = open(filename, O_RDONLY);
	else if (redir_type == TOKEN_HEREDOC)
		return (heredoc(&new_file, filename, &f_con));
	else if (redir_type == TOKEN_REDIR_OUT)
		new_file->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir_type == TOKEN_APPEND)
		new_file->fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (new_file->fd == -1)
		return (clean_mem(new_file, NULL, NULL, errno));
	if (redir_type == TOKEN_REDIR_IN || redir_type == TOKEN_HEREDOC)
		f_con->last_in_fd = new_file->fd;
	else
		f_con->last_out_fd = new_file->fd;
	new_file->filename = ft_strdup(filename);
	add_file_back(&f_con->lst, new_file);
	if (!new_file->filename)
		return (-1);
	return (0);
}
