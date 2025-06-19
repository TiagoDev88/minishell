/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:17:00 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/06/19 16:48:58 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/token.h"

int main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = readline("miniShell> ");
		if (!line)
			break;
		add_history(line);
		tokens = tokenize(line);
		t_token *tmp = tokens;
		while (tmp)
		{
			printf("Token: [%d] \"%s\"\n", tmp->type, tmp->value);
			tmp = tmp->next;
		}
		free_tokens(tokens);
		free(line);
	}
}

