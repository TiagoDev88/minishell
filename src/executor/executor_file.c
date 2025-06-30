/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:51:27 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/30 15:52:06 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_files(t_file **file_lst)
{
	t_file	*curr;
	t_file	*tmp;

	if (file_lst)
	{
		curr = *file_lst;
		while (curr)
		{
			tmp = curr->next;
			if (curr->fd != -1)
				close(curr->fd);
			free(curr);
			curr = tmp;
		}
		*file_lst = NULL;
	}
}

void	close_files(t_files_container *files_container)
{
	t_file	*curr;

	if (!files_container->lst)
		return ;
	curr = files_container->lst;
	while (curr)
	{
		if (curr->fd != -1)
			close(curr->fd);
		curr->fd = -1;
		curr = curr->next;
	}
}

void		add_file_back(t_file **file_lst, t_file *new_file)
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

int	add_file(t_files_container *files_container, char *filename, int redir_type)
{
	t_file	*new_file;

	new_file = malloc(sizeof(t_file));
	if (!new_file)
		return (0);
	new_file->next = NULL;
	if (redir_type == TOKEN_REDIR_IN)
		new_file->fd = open(filename, O_RDONLY);
	else if (redir_type == TOKEN_REDIR_OUT)
		new_file->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir_type == TOKEN_APPEND)
		new_file->fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (new_file->fd == -1)
	{
		free(new_file);
		perror("");
		return (0);
	}
	if (redir_type == TOKEN_REDIR_IN || redir_type == TOKEN_HEREDOC)
		files_container->last_in_fd = new_file->fd;
	else
		files_container->last_out_fd = new_file->fd;
	add_file_back(&files_container->lst, new_file);
	return (1);
}

int	open_files(t_token **curr_token, t_files_container *files_container)
{
	while (*curr_token && ((*curr_token)->type >= TOKEN_REDIR_OUT && (*curr_token)->type <= TOKEN_HEREDOC))
	{
		if ((*curr_token)->type != TOKEN_HEREDOC)
			if (!add_file(files_container, (*curr_token)->next->value, (*curr_token)->type))
			{
				EXIT_STATUS = 1;
				return (0);
			}
		*curr_token = (*curr_token)->next->next;
	}
	return (1);
}
