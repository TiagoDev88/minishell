/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:17:00 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/10 15:14:00 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

int g_exit_status = 0;

#ifndef TEST_MODE
	#define TEST_MODE 0
#endif

typedef struct s_minishell
{
	t_exec		exec;
	t_token		*tokens;
	t_parser	parser;
}	t_minishell;

void sigint_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	g_exit_status = 130;
}

int is_interactive(void)
{
    return isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
}


int main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	t_shell shell;
	char	*line;
	char *dir = NULL;
	char *tmp_dir = NULL;
	
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	t_envp *tmp = NULL;
	ft_memset(&shell, 0, sizeof(t_shell));
	copy_env(envp, &shell.envp);
	while (1)
	{
		tmp_dir = getcwd(NULL, 0);  //dar free a dir, pk e alocado
		dir = ft_strjoin(tmp_dir, "$ ");
		free(tmp_dir);
		if (is_interactive())
			line = readline(dir);
		else
		{
			line = get_next_line(STDIN_FILENO);
			line[ft_strlen(line) - 1] = '\0';
		}
		free(dir);
		if (!line)
			break;
		add_history(line);
		shell.tokens = tokenize(line, shell.envp);
		if (parser(&shell.parser, shell.tokens))
			executor(&shell, envp);
		exit_clean(&shell, -1);
		//cmd_clear(&shell.parser.cmd_lst, 0);
		//free_tokens(&shell.tokens);
		free(line);
		if (TEST_MODE == 1)
		{
			rl_clear_history();
			exit(g_exit_status);
		}
	}
	printf("Saiu\n");
	rl_clear_history();
	exit_clean(&shell, 0);
	return (0);
}

