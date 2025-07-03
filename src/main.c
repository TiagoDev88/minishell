/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:17:00 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/03 12:15:27 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	char	*line;
	t_token	*tokens;
	char *dir = NULL;
	t_cmd *lst = NULL;


	dir = getcwd(NULL, 0);  //dar free a dir, pk e alocado
	dir = ft_strjoin(dir, "$ ");

	while (1)
	{
		line = readline(dir);
		if (!line)
			break;
		add_history(line);
		tokens = tokenize(line, envp);
		parser(&lst, tokens);
		execute(tokens, lst, envp);
		cmd_clear(&lst, 0);
		free_tokens(tokens);
		free(line);
	}
	return (0);
}

