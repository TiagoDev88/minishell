
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
static int valid_key(char *cmd)
{
	int i;

	i = 0;
	if (!cmd || (!ft_isalpha(cmd[0]) && cmd[0] != '_'))
		return (0);
	while (cmd[i] && cmd[i] != '=' && !(cmd[i] == '+' && cmd[i + 1] == '='))
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
		i++;
	}
	if (cmd[i] == '+' && cmd[i + 1] == '=')
		return (2);
	return (1);
}

static void	add_export_env(char *envp, t_envp **env_list)
{
	char	*key;
	char	*value;
	char	*equal;
	int		key_len;

	equal = ft_strchr(envp, '=');
	if (equal)
	{
		key_len = equal - envp;
		//printf("key len %d\n", key_len);
		key = ft_substr(envp, 0, key_len);
		value = ft_strdup(equal + 1);
		//printf("key: %s e value %s\n", key, value);
		add_envp(env_list, new_envp(key, '=', value));
	}
	else
	{
		key = ft_strdup(envp);
		add_envp(env_list, new_envp(key, 0, NULL));
	}
	//assign_indexes(*env_list);
}


static void	update_export_env(char *envp, t_envp *node, int conc)
{
	char	*value;
	char	*equal;
	int		key_len;
	char	*tmp;

	equal = ft_strchr(envp, '=');
	if (!equal || !node)
		return ;
	key_len = equal - envp;
	value = ft_strdup(equal + 1);
	if (conc == 2)
	{
		tmp = ft_strjoin(node->value, value);
		free(node->value);
		node->value = tmp;
	}
	else
	{
		free(node->value);
		node->value = value;
	}
	node->flag = '=';
}


//TODO talvez fazer um if, else para ver se o primeiro carcter letra ou _
// e aqui adicionar a lista, caso nao seja, dar erro "bash: export: `10=9': not a valid identifier" com exemplo de "export 10=9"
int	ft_export(t_cmd *cmd, t_envp **envp)
{
	if (!cmd || !(*envp) || !envp)
		return (1);
	if (cmd->cmd_args[1] == NULL)
		return (print_export_envp(*envp), 0); // chamar a funcao de printar.
	t_cmd *tmp;
	int i;
	int j;
	int len;
	t_envp *tenvp;
	int flag = 0;
	int plus = 0;
	char *p_plus;

	tmp = cmd;

	i = 1;
	while (tmp->cmd_args[i])
	{
		j = valid_key(tmp->cmd_args[i]);
		printf("valor da valid key %d\n", j);
		tenvp = *envp;
		flag = 0;
		while (tenvp)
		{
			len = ft_strlen(tenvp->key);
			//printf("valor da LEN %d do no %s\n", len, tenvp->key);
			if (!ft_strncmp(tenvp->key, tmp->cmd_args[i], len))
			{
				printf("entrou\n");
				update_export_env(tmp->cmd_args[i], tenvp, j);
				flag = 1;
				break;
			}
			tenvp = tenvp->next;
		}
		if (flag == 0 && j > 0)
			add_export_env(tmp->cmd_args[i], envp);
		//printf("valor do comando KEY: %s\n",tmp->cmd_args[i]);
		i++;
	}
	return (0);
}

