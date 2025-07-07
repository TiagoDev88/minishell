
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

//TODO tratar destes casos
// export abc= (guarda nas variaveis, desta forma. abc="")
// se for export abc (ele guarda nas variaves desta forma abc sem o ="")
// export funcionar com +=
// variavel chamada teste que o valor e 'a' e se eu lhe meter um export test+=b isto tem que ser 'ab' (talvez tratar talvez nao, confirmar COM O GRANDE DIOGO)
// export test= (fica so test=)
// export test (fica so test e nao aparece no env)
// o export test-= (tem que dar erro)
/*
bash-5.2$ export test-=
bash: export: `test-=': not a valid identifier
bash-5.2$ echo $?
1
*/

//TODO concatenar ou adicionar variaveis novas.
static int	valid_key(char *cmd)
{
	int j;
	int flag;

	j = 0;
	flag = 0;
	if (ft_isdigit(cmd[0]))
		return (0);
	while(cmd[j] && cmd[j] != '=' && (ft_isalpha(cmd[0]) || cmd[0] == '_'))
	{
		flag = 0;
		if (!ft_isalnum(cmd[j]) && cmd[j] != '_')
			break;
		flag = 1;
		j++;
	}
	if (cmd[j] == '+' && cmd[j + 1] == '=')
		return (printf("concatenar\n"), 2);
	if (flag == 1)
		printf("valido\n");
	return (0);
}


//TODO talvez fazer um if, else para ver se o primeiro carcter letra ou _
// e aqui adicionar a lista, caso nao seja, dar erro "bash: export: `10=9': not a valid identifier" com exemplo de "export 10=9"
int	ft_export(t_cmd *cmd, t_envp ** envp)
{
	//printf("conteudo no comando: %s\n", cmd->cmd_args[0]);
	if (!cmd || !(*envp) || !envp)
		return (1);
	if (cmd->cmd_args[1] == NULL)
		return (print_export_envp(*envp), 0); // chamar a funcao de printar.
	t_cmd *tmp;
	int i;
	int j;

	tmp = cmd;
	i = 1;
	j = 0;
	while (tmp->cmd_args[i])
	{
		valid_key(tmp->cmd_args[i]);
		j = 0;
		// while (ft_isalnum(tmp->cmd_args[i][j]) && ft_isalpha(tmp->cmd_args[i][0]))
		// {
		// 	//if (ft_isdigit(tmp->cmd_args[i][0]))
		// 	printf("printas conteudo no comando %d caracter %c %s\n", i, tmp->cmd_args[i][j], tmp->cmd_args[i]);
		// 	j++;
		// }
		i++;
	}
	return (0);
}

