

#include "../includes/minishell.h"



int	execute_command(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd_args || !cmd->cmd_args[0])
		return (1);
	if (ft_strncmp(cmd->cmd_args[0], "echo", 5) == 0)
		return (ft_echo(cmd));
	return (0);
}

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
		tokens = tokenize(line, envp);
		t_cmd *lst = NULL;
		parser(&lst, tokens);
		while (lst)
		{
			// printf("COMMAND: ");
			// int i = 0;
			// while (lst->cmd_args[i])
			// {
			// 	printf("%s ", lst->cmd_args[i]);
			// 	i++;
			// }
			// printf("\n");
			execute_command(lst);
			lst = lst->next;
		}
		free_tokens(&tokens);
		free(line);
	}
	return (0);
}