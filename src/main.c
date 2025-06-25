/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:17:00 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/06/25 00:55:31 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		t_cmd *lst = NULL;
		parser(&lst, tokens);
		if (lst)
		{
			while (lst)
			{
				printf("COMMAND\n");
				int i = 0;
				while (lst->cmd[i])
				{
					printf("%s\n", lst->cmd[i]);
					i++;
				}
				while (lst->redir_in)
				{
					printf("IN: FILENAME: %s TYPE: %i\n", lst->redir_in->filename, lst->redir_in->type);
					lst->redir_in = lst->redir_in->next;
				}
				while (lst->redir_out)
				{
					printf("OUT: FILENAME: %s TYPE: %i\n", lst->redir_out->filename, lst->redir_out->type);
					lst->redir_out = lst->redir_out->next;
				}
				lst = lst->next;
			}
		}
		free_tokens(tokens);
		free(line);
	}
	return (0);
}

