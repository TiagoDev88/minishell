/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:17:00 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/06/20 16:35:27 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

int main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	char	*line;
	t_token	*tokens;
	char *dir = NULL;


	dir = getcwd(NULL, 0);  //dar free a dir, pk e alocado
	dir = ft_strjoin(dir, "$ ");

	while (1)
	{
		line = readline(dir);
		if (!line)
			break;
		add_history(line);
		tokens = tokenize(line);
		t_token *tmp = tokens;
		while (tmp)
		{
			printf("Token: [%d] |%s| FLAG |%d|\n", tmp->type, tmp->value, tmp->double_quote);
			tmp = tmp->next;
		}
		free_tokens(tokens);
		free(line);
	}
	return (0);
}

