

#include "../includes/minishell.h"
#include "../includes/utils.h"

void sigint_handler(int sig)
{
    (void)sig;
	clear_history();
	rl_clear_signals();
 	write(1, "\nShell encerrada por SIGINT (Ctrl+C)\n", 37);
	exit(EXIT_SUCCESS);
}

int execute_command(t_cmd **cmd, t_envp **envp)
{
	if (!cmd || !*cmd || !(*cmd)->cmd_args || !(*cmd)->cmd_args[0])
		return (1);
	if (ft_strncmp((*cmd)->cmd_args[0], "echo", 5) == 0)
		return (ft_echo(*cmd));
	if (ft_strncmp((*cmd)->cmd_args[0], "exit", 5) == 0)
		return (ft_exit(cmd));
	if (ft_strncmp((*cmd)->cmd_args[0], "cd", 3) == 0)
        return (ft_cd(*cmd));
	if (ft_strncmp((*cmd)->cmd_args[0], "env", 4) == 0)
        return (ft_env(*cmd, *envp));
	if (ft_strncmp((*cmd)->cmd_args[0], "export", 7) == 0)
		return (ft_export(*cmd, envp));
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

	t_envp *cp_envp = NULL;
	copy_env(envp, &cp_envp);
	// t_envp *tmp;
	// tmp = cp_envp;
	// while (tmp)
	// {
	// 	printf("key: %s | ", tmp->key);
	// 	if (tmp->flag == '=')
	// 		printf("value: %s\n", tmp->value);
	// 	else
	// 		printf("sem valor (só exportado, não no env)\n");
	// 	tmp = tmp->next;
	// }
	// int i = 0;
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }

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
		tokens = tokenize(line, &cp_envp);
		t_token *tmp1 = tokens;
		while (tmp1)
		{
			printf("Token: [%d] |%s|\n", tmp1->type, tmp1->value);
			tmp1 = tmp1->next;
		}
		parser(&lst, tokens);
		free_tokens(&tokens);
		t_cmd *tmp = lst;
		while (tmp)
		{
			// printf("COMMAND: ");
			// int i = 0;
			// while (lst->cmd_args[i])
			// {
			// 	printf("%s ", lst->cmd_args[i]);
			// 	i++;
			// }
			// printf("\n");
			execute_command(&tmp, &cp_envp);
			tmp = tmp->next;
		}
		cmd_clear(&lst, 10);
		//free_envp(&cp_envp); // para testar se tem links nas envs

		//printf("argumentos %s \n", lst->cmd_args[0]);
		free(line);
	}
	free_envp(&cp_envp);
	free(dir);
	return (0);
}
