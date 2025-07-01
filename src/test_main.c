

#include "../includes/minishell.h"

void sigint_handler(int sig)
{
    (void)sig;
	clear_history();
	rl_clear_signals();
 	write(1, "\nShell encerrada por SIGINT (Ctrl+C)\n", 37);
	exit(EXIT_SUCCESS);
}

int execute_command(t_cmd **cmd)
{
	if (!cmd || !*cmd || !(*cmd)->cmd_args || !(*cmd)->cmd_args[0])
		return (1);
	if (ft_strncmp((*cmd)->cmd_args[0], "echo", 5) == 0)
		return (ft_echo(*cmd));
	if (ft_strncmp((*cmd)->cmd_args[0], "exit", 5) == 0)
		return (ft_exit(cmd));
	if (ft_strncmp((*cmd)->cmd_args[0], "cd", 3) == 0)
        return (ft_cd(*cmd));
	return (0);
}

//TODO tratar de fazer uma copia dos envs, para nao alterar os originais
// tratar de fazer free dos envs, e de todas as variaveis que sao alocadas
// tratar de fazer free dos tokens, e de todas as variaveis que sao alocadas
// tratar de fazer free dos comandos, e de todas as variaveis que sao alocadas
// tratar de fazer free dos argumentos, e de todas as variaveis que sao alocadas
// tratar de fazer free dos pipes, e de todas as variaveis que sao alocadas
// tratar de fazer free dos redirecionamentos, e de todas as variaveis que sao alocadas
// talvez criar uma estrutura por causa das ENVs

int main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	char	*line;
	char *dir = NULL;
	char *cwd = NULL;
	t_token	*tokens;
	t_cmd *lst = NULL;
	signal(SIGINT, sigint_handler);
	

	while (1)
	{

		//printf("argumentos %s \n", lst->cmd_args[0]);
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
		parser(&lst, tokens);
		free_tokens(&tokens);
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
			execute_command(&lst);
			lst = lst->next;
		}
		cmd_clear(&lst, 10);
		free(line);
	}
	free(dir);
	return (0);
}
