/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc_reader.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:55:03 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/23 02:46:18 by edfreder         ###   ########.fr       */
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
static int	is_delimiter(char *line, char *delimiter)
{
	if (ft_strlen(line) == ft_strlen(delimiter)
		&& !ft_strncmp(line, delimiter, ft_strlen(line)))
	{
		free(line);
		return (1);
	}
	return (0);
}

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = 130;
	close(0);
}

static void	heredoc_sigpipe_handler(int sig)
{
	(void)sig;
	g_signal = 128 + SIGPIPE;
}

static void	write_heredoc(int fd, char *del)
{
	char	*line;
	int		dup_stdin;

	dup_stdin = dup(STDIN_FILENO);
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
	dup2(dup_stdin, STDIN_FILENO);
	close(dup_stdin);
}

static void	wait_heredoc_fork(pid_t pid, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_signal = 130;
		shell->exec.heredoc_signed = 1;
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_signal = 130;
		shell->exec.heredoc_signed = 1;
	}
}

void	read_heredoc(t_shell *shell, char *filename, char *del)
{
	int		fd;
	pid_t	pid;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_file_err(filename, strerror(errno), 1);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		exit_clean(shell, errno, 1);
	else if (pid == 0)
	{
		signal(SIGPIPE, heredoc_sigpipe_handler);
		signal(SIGINT, heredoc_sigint_handler);
		write_heredoc(fd, del);
		close(fd);
		clean_heredocs_s(&shell->exec.heredocs_lst, 0);
		exit_clean(shell, g_signal, 1);
	}
	else
	{
		close(fd);
		wait_heredoc_fork(pid, shell);
		signal(SIGINT, sigint_handler);
	}
}
