/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:17:00 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/03 22:33:19 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exit_status = 0;

void print_things(t_cmd *lst, t_token *tokens)
{
	t_token *curr = tokens;
	while (curr)
	{
		printf("TOKEN: %s TYPE: %i", curr->value, curr->type);
		if (curr->next)
			printf(", ");
		curr = curr->next;
	}
	printf("\n");
	if (!lst)
	{
		printf("Lista vazia\n");
	}
	else
	{
		t_cmd *curr_cmd = lst;
		while (curr_cmd)
		{
			printf("ARGS_LST: ");
			if (curr_cmd->args_lst)
			{
				t_list *curr_lst = curr_cmd->args_lst;
				while (curr_lst != NULL)
				{
					printf("%s ", (char *)curr_lst->content);
					curr_lst = curr_lst->next;
				}
				printf("\n");
			}
			int i = 0;
			if (curr_cmd->cmd_args && curr_cmd->cmd_args[0])
			{
				printf("CMDS_LST: ");
				while (curr_cmd->cmd_args[i] != NULL)
				{
					printf("%s ", curr_cmd->cmd_args[i]);
					i++;
				}
				printf("\n");
			}
			printf("REDIR_INS: ");
			t_redir *curr_in = curr_cmd->redir_in;
			while (curr_in)
			{
				printf("%s ", curr_cmd->redir_in->filename);
				curr_in = curr_in->next;
			}
			printf("\n");
			printf("REDIR_OUTS: ");
			t_redir *curr_out = curr_cmd->redir_out;
			while (curr_out)
			{
				printf("%s ", curr_cmd->redir_out->filename);
				curr_out = curr_out->next;
			}
			printf("\n");
			curr_cmd = curr_cmd->next;
		}
	}
}

int main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	char	*line;
	t_token	*tokens;
	char *dir = NULL;
	t_parser	parser_s;
	ft_memset(&parser_s, 0, sizeof(t_parser));
	dir = getcwd(NULL, 0);  //dar free a dir, pk e alocado
	dir = ft_strjoin(dir, "$ ");
	printf("Ola entrei no Minishell!\n");
	while (1)
	{
		line = readline(dir);
		if (!line)
		{
			printf("no line\n");
			return (1);
		}
		if (ft_strncmp(line, "exit", 4) == 0)
			return (1);
		add_history(line);
		tokens = tokenize(line, envp);
		if (parser(&parser_s, tokens))
			execute(tokens, parser_s.cmd_lst, envp);
		//parser(&parser_s, tokens);
		//print_things(parser_s.cmd_lst, tokens);
		free_tokens(tokens);
		free(line);
		cmd_clear(&parser_s.cmd_lst, 0);
	}
	printf("sai do programa\n");
	free_tokens(tokens);
	free(line);
	cmd_clear(&parser_s.cmd_lst, 0);
	rl_clear_history();
	return (0);
}

