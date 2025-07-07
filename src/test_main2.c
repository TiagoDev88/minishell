/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:17:00 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/07 22:15:14 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_exit_status = 0;

int main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	char	*line;
	t_token	*tokens;
	char *dir = NULL;
	//t_cmd *lst = NULL;

	t_parser parserola;
	ft_memset(&parserola, 0, sizeof(t_parser));
	dir = getcwd(NULL, 0);  //dar free a dir, pk e alocado
	dir = ft_strjoin(dir, "$ ");

	while (1)
	{
		line = readline(dir);
		if (!line)
			break;
		add_history(line);
		tokens = tokenize(line, envp);
		t_token *tmp;
		tmp = tokens;
		while (tmp)
		{
			printf("TOKEN |%s|\n", tmp->value);
			tmp = tmp->next;
		}
		parser(&parserola, tokens);
		executor(tokens, parserola.cmd_lst, envp);
		cmd_clear(&parserola.cmd_lst, 0);
		free_tokens(tokens);
		free(line);
	}
	return (0);
}

