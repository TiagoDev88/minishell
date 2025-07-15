/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:07:53 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/15 23:32:15 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * is_delimiter - Checks if a given line matches the heredoc delimiter.
 * @line: The input line read from stdin (with newline).
 * @delimiter: The heredoc delimiter string.
 *
 * Compares the line (excluding the trailing newline) to the delimiter.
 * Frees the line if it matches.
 *
 * Return: 1 if line matches delimiter, 0 otherwise.
 */

int	is_delimiter(char *line, char *delimiter)
{
	if (ft_strlen(line) - 1 == ft_strlen(delimiter)
		&& !ft_strncmp(line, delimiter, ft_strlen(line) - 1))
	{
		free(line);
		return (1);
	}
	return (0);
}

/**
 * get_heredoc_filename - Generates a unique filename for a heredoc.
 * @n_heredocs: The current count of heredocs processed.
 *
 * Creates a string ".heredoc_<n>" where <n> is the heredoc index.
 * Allocates memory for the string, which must be freed by caller.
 *
 * Return: Newly allocated heredoc filename string or NULL on failure.
 */
char	*get_heredoc_filename(int n_heredocs)
{
	char	*n_heredocs_str;
	char	*filename;

	n_heredocs_str = ft_itoa(n_heredocs);
	if (!n_heredocs_str)
		return (NULL);
	filename = ft_strjoin(".heredoc_", n_heredocs_str);
	free(n_heredocs_str);
	if (!filename)
		return (NULL);
	return (filename);
}

/**
 * heredoc - Reads heredoc input until delimiter is reached and saves it.
 * @new: Pointer to a t_file struct to hold heredoc file info.
 * @del: The heredoc delimiter string.
 * @f_con: Pointer to the files container structure managing heredoc state.
 *
 * Increments heredoc count, generates unique filename, opens a temporary file
 * for writing heredoc contents, reads lines from stdin until the delimiter is
 * matched, writes input to the file, then reopens it for reading.
 * Adds the heredoc file info to the files container list.
 *
 * Return: 0 on success, -1 on failure (e.g., memory allocation).
 */
int	heredoc(t_file **new, char *del, t_files_container **f_con)
{
	char	*line;

	(*f_con)->heredocs++;
	(*new)->filename = get_heredoc_filename((*f_con)->heredocs);
	if (!(*new)->filename)
		return (clean_mem(*new, NULL, NULL, -1));
	(*new)->unlink = 1;
	(*new)->fd = open((*new)->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (is_delimiter(line, del))
			break ;
		ft_putstr_fd(line, (*new)->fd);
		free(line);
	}
	close((*new)->fd);
	(*new)->fd = open((*new)->filename, O_RDONLY);
	(*f_con)->last_in_fd = (*new)->fd;
	add_file_back(&(*f_con)->lst, *new);
	return (0);
}
