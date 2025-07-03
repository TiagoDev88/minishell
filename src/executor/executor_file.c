/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:51:27 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/03 14:35:15 by edfreder         ###   ########.fr       */
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
			if (curr->fd != -1 && curr->fd > 2)
				close(curr->fd);
			printf("%i %i %s\n", curr->fd, curr->unlink, curr->filename);
			if (curr->unlink)
				unlink(curr->filename);
			free(curr->filename);
			free(curr);
			curr = tmp;
		}
		*file_lst = NULL;
	}
}

void	close_files(t_files_container *files_container)
{
	t_file	*curr;

	if (files_container->lst)
		return ;
	curr = files_container->lst;
	while (curr)
	{
		if (curr->fd != STDIN_FILENO || curr->fd != STDOUT_FILENO)
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

t_file *create_file_node(void)
{
	t_file	*new_file;

	new_file = malloc(sizeof(t_file));
	if (!new_file)
		return (NULL);
	new_file->fd = -2;
	new_file->unlink = 0;
	new_file->filename = NULL;
	new_file->next = NULL;
	return (new_file);
}

int	add_file(t_files_container *files_container, char *filename, int redir_type)
{
	t_file	*new_file;

	new_file = create_file_node();
	if (!new_file)
		return (-1);
	if (redir_type == TOKEN_REDIR_IN)
		new_file->fd = open(filename, O_RDONLY);
	else if (redir_type == TOKEN_HEREDOC)
		return (heredoc(&new_file, filename, &files_container));
	else if (redir_type == TOKEN_REDIR_OUT)
		new_file->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir_type == TOKEN_APPEND)
		new_file->fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (new_file->fd == -1)
		return (clean_mem(new_file, NULL, NULL, errno));
	if (redir_type == TOKEN_REDIR_IN || redir_type == TOKEN_HEREDOC)
		files_container->last_in_fd = new_file->fd;
	else
		files_container->last_out_fd = new_file->fd;
	new_file->filename = ft_strdup(filename);
	add_file_back(&files_container->lst, new_file);
	if (!new_file->filename)
		return (-1);
	return (0);
}

int	open_files(t_token **curr_token, t_exec *exec)
{
	int	exit_status;

	exit_status = 0;
	while (*curr_token && ((*curr_token)->type >= TOKEN_REDIR_OUT && (*curr_token)->type <= TOKEN_HEREDOC))
	{
		exit_status = add_file(&exec->files_container, (*curr_token)->next->value, (*curr_token)->type);
		if (exit_status == -1)
		{
			print_error_msg(NULL, "malloc: error", 1);
			exit_clean(exec, 2);
		}
		if (exit_status > 0)
		{
			EXIT_STATUS = 1;
			print_file_err_and_return((*curr_token)->next->value, strerror(exit_status), 0);
			while (*curr_token && ((*curr_token)->type >= TOKEN_REDIR_OUT && (*curr_token)->type <= TOKEN_HEREDOC))
				*curr_token = (*curr_token)->next->next;
			return(0);
		}
		*curr_token = (*curr_token)->next->next;
	}
	return (1);
}
