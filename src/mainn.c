#include "../includes/minishell.h"

int g_signal = 0;

void sigint_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	g_signal = 130;
}

char	*get_actual_dir(t_shell *shell)
{
	char	*tmp_dir;
	char	*dir;

	tmp_dir = getcwd(NULL, 0);
	if (!tmp_dir)
		exit_clean(shell, ENOMEM, 1);
	dir = ft_strjoin(tmp_dir, "$ ");
	free(tmp_dir);
	if (!dir)
		exit_clean(shell, ENOMEM, 1);
	return (dir);
}

char	*get_prompt_line(t_shell *shell, char *dir)
{
	char	*line;

	line = readline(dir);
	/*
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		line = readline(dir);
	else
	{
		line = get_next_line(STDIN_FILENO);
		line[ft_strlen(line) - 1] = '\0';
	}
	*/
	free(dir);
	if (line)
	{
		if (g_signal > 0)
			shell->last_status_code = g_signal;
		g_signal = 0;
	}
	return (line);
}

void	initiate_minishell(int argc, char **argv, t_shell *shell, char **envp)

{
	(void)argc;
	(void)argv;
	ft_memset(shell, 0, sizeof(t_shell));
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	copy_env(envp, &shell->envp);
}

int main(int argc, char *argv[], char **envp)
{
	t_shell shell;
	char	*line;
	char	*dir;

	if (argc != 1)
		return (ft_putstr_fd("Arguments are not accepted!\n", 2), 1);
	initiate_minishell(argc, argv, &shell, envp);
	while (1)
	{
		dir = get_actual_dir(&shell);
		line = get_prompt_line(&shell, dir);
		if (!line)
			break ;
		shell.tokens = tokenize(line, &shell.envp, &shell);
		if (!shell.tokens && (line[0] == ' ' || line[0] == '	'))
			continue ;
		add_history(line);
		free(line);
		line = NULL;
		if (parser(&shell.parser, shell.tokens, &shell))
			executor(&shell, envp);
		exit_clean(&shell, -1, 0);
	}
	ft_putendl_fd("exit", 1);
	exit_clean(&shell, 0, 1);
}
