/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:07:53 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/23 02:48:04 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_heredocs_s(t_heredoc **hd_lst, int is_to_unlink)
{
	t_heredoc	*curr;
	t_heredoc	*tmp;

	curr = *hd_lst;
	while (curr)
	{
		tmp = curr->next;
		if (curr->del)
			free(curr->del);
		if (curr->filename)
		{
			if (is_to_unlink)
				unlink(curr->filename);
			free(curr->filename);
		}
		free(curr);
		curr = tmp;
	}
	*hd_lst = NULL;
}

static char	*get_heredoc_filename(int *n_heredocs)
{
	char	*n_heredocs_str;
	char	*filename;

	n_heredocs_str = ft_itoa(*n_heredocs);
	if (!n_heredocs_str)
		return (NULL);
	filename = ft_strjoin(".heredoc_", n_heredocs_str);
	free(n_heredocs_str);
	(*n_heredocs)++;
	return (filename);
}

static void	add_heredoc_back(t_heredoc **hd_lst, t_heredoc *new)
{
	t_heredoc	*curr;

	if (!(*hd_lst))
		*hd_lst = new;
	else
	{
		curr = *hd_lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

static void create_heredoc(t_shell *shell, t_heredoc **hd_lst, char *del)
{
	t_heredoc *new;

	new = malloc(sizeof(t_heredoc));
	if (!new)
		exit_clean(shell, ENOMEM, 1);
	add_heredoc_back(hd_lst, new);
	new->next = NULL;
	new->del = ft_strdup(del);
	if (!new->del)
		exit_clean(shell, ENOMEM, 1);
	new->filename = get_heredoc_filename(&shell->exec.files_container.heredocs);
	if (!new->filename)
	{
		free(new->del);
		exit_clean(shell, ENOMEM, 1);
	}
	read_heredoc(shell, new->filename, new->del);
}

void	open_heredocs(t_shell *shell)
{
	t_token	*curr;

	curr = shell->tokens;
	while (curr)
	{
		if (curr->type == TOKEN_HEREDOC)
		{
			create_heredoc(shell, &shell->exec.heredocs_lst, curr->next->value);
			if (curr->next->next)
				curr = curr->next->next;
			else
				curr = curr->next;
		}
		else
		{
			curr = curr->next;
		}
	}
}