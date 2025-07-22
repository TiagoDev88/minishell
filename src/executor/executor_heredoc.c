/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:07:53 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/22 15:45:51 by edfreder         ###   ########.fr       */
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
	if (ft_strlen(line) == ft_strlen(delimiter)
		&& !ft_strncmp(line, delimiter, ft_strlen(line)))
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
 * @brief Signal handler for SIGINT during heredoc input.
 *
 * This function is triggered when the user presses Ctrl+C
 * during a heredoc. It writes a newline to the terminal,
 * sets a global exit status (`g_signal`), and closes stdin
 * to interrupt the heredoc reading loop cleanly.
 *
 * @param sig The received signal number (unused).
 */
void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = 130;
	close(0);
}

/**
 * @brief Reads user input for a heredoc until the delimiter or interruption.
 *
 * Prompts the user with `> ` and reads lines using `readline()`.
 * Each line is written to the specified file descriptor, unless
 * it matches the given delimiter. Handles interruptions via global
 * signal status (`g_signal`).
 *
 * @param fd File descriptor where heredoc content is written.
 * @param del The string delimiter to stop reading.
 * @return int Exit code: 0 if finished normally, 130 if interrupted.
 */
int	read_heredoc(int fd, char *del)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_delimiter(line, del))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (!line)
	{
		if (g_signal == 130)
			return (130);
		else
			return (0);
	}
	return (0);
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
	int	heredoc_status;
	int back_up_stdin;

	if ((*f_con)->is_pipe_fd == 1) 
	{
		close((*f_con)->last_in_fd);
		(*f_con)->is_pipe_fd = 0;
	}
	signal(SIGINT, heredoc_sigint_handler);
	back_up_stdin = dup(STDIN_FILENO);
	heredoc_status = 0;
	(*f_con)->heredocs++;
	(*new)->filename = get_heredoc_filename((*f_con)->heredocs);
	if (!(*new)->filename)
		return (clean_mem(*new, NULL, NULL, -1));
	(*new)->unlink = 1;
	(*new)->fd = open((*new)->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	heredoc_status = read_heredoc((*new)->fd, del);
	dup2(back_up_stdin, STDIN_FILENO);
	close(back_up_stdin);
	close((*new)->fd);
	(*new)->fd = open((*new)->filename, O_RDONLY);
	(*f_con)->last_in_fd = (*new)->fd;
	signal(SIGINT, sigint_handler);
	return (heredoc_status);
}
