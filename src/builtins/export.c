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

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int	ft_export(t_cmd *cmd, t_envp ** envp)
{
	printf("conteudo no comando: %s\n", cmd->cmd_args[0]);
	if (!cmd || !(*envp) || !envp)
		return (1);
	if (cmd->cmd_args[1] == NULL)
		return (print_envp(*envp), 0); // chamar a funcao de printar.
	t_cmd *tmp;
	int i = 1;
	int j = 0;

	tmp = cmd;
	while (tmp->cmd_args[i])
	{
		j = 0;
		while (ft_isalnum(tmp->cmd_args[i][j]) && ft_isalpha(tmp->cmd_args[i][0]))
		{
			printf("printas conteudo no comando %d caracter %c %s\n", i, tmp->cmd_args[i][j], tmp->cmd_args[i]);
			j++;
		}
		i++;
		//tmp = tmp->next;
	}
	return (0);
}