/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:07:53 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/03 00:30:55 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_delimiter(char *line, char *delimiter)
{
	return (ft_strlen(line) - 1 == ft_strlen(delimiter)
	&& !ft_strncmp(line, delimiter, ft_strlen(line) - 1));
}

char	*get_heredoc_filename(int n_heredocs)
{
	char *n_heredocs_str;
	char *filename;

	n_heredocs_str = ft_itoa(n_heredocs);
	if (!n_heredocs_str)
		return (NULL);
	filename = ft_strjoin(".heredoc_", n_heredocs_str);
	if (!filename)
	{
		free(n_heredocs_str);
		return (NULL);
	}
	return (filename);
}

int	heredoc(t_file **new_file, char *delimiter, t_files_container **files_container)
{
	char	*line;
	char	*heredoc_filename;

	(*files_container)->heredocs++;
	(*new_file)->filename = get_heredoc_filename((*files_container)->heredocs);
	if (!(*new_file)->filename)
		return (clean_mem(*new_file, NULL, NULL, -1));
	(*new_file)->unlink = 1;
	(*new_file)->fd = open((*new_file)->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (is_delimiter(line, delimiter))
			break ;
		ft_putstr_fd(line, (*new_file)->fd);
		free(line);
	}
	close((*new_file)->fd);
	(*new_file)->fd = open((*new_file)->filename, O_RDONLY);
	(*files_container)->last_in_fd = (*new_file)->fd;
	add_file_back(&(*files_container)->lst, *new_file);
	return (0);
}
