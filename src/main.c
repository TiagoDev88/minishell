/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:17:00 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/06/29 13:09:33 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

// usar para leaks valgrind --leak-check=full --show-leak-kinds=definite  ./minishell

void sigint_handler(int sig)
{
    (void)sig;
	clear_history();
	rl_clear_signals();
 	write(1, "\nShell encerrada por SIGINT (Ctrl+C)\n", 37);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	char	*line;
	char *dir = NULL;
	char *cwd = NULL;
	t_token	*tokens;

	signal(SIGINT, sigint_handler);
	

	while (1)
	{
		free(dir);
		cwd = getcwd(NULL, 0);  //dar free a dir, pk e alocado
		if (!cwd)
			break;
		dir = ft_strjoin(cwd, "$ ");
		free(cwd);
		line = readline(dir);
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line)
			add_history(line);
			
		tokens = tokenize(line, envp);
		t_token *tmp = tokens;
		while (tmp)
		{
			printf("Token: [%d] |%s|\n", tmp->type, tmp->value);
			tmp = tmp->next;
		}
		free_tokens(&tokens);
		free(line);
	}
	free(dir);
	return (0);
}

