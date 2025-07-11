

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

static int	unset_first_envp(char *cmd_env, t_envp **envp)
{
	t_envp	*head;

	head = *envp;
	if (!ft_strncmp(cmd_env, head->key, ft_strlen(head->key)))
	{
		*envp = head->next;
		free(head->key);
		if (head->value)
			free(head->value);
		free(head);
		return (1);
	}
	return (0);
}

int	ft_unset(t_cmd *cmd, t_envp **envp)
{
	if (!cmd || !cmd->cmd_args[1] || !envp || !*envp)
		return (1);
	t_envp *tmp;
	t_envp *curr;
	int i;

	i = 1;
	while (cmd->cmd_args[i])
	{
		if (unset_first_envp(cmd->cmd_args[i], envp))
			return (0);
		curr = (*envp)->next;
		while (curr)
		{
			if (!ft_strncmp(cmd->cmd_args[i], curr->key, ft_strlen(curr->key)))
			{
				tmp->next = curr->next;
				free(curr->key);
				if (curr->value)
					free(curr->value);
				free(curr);
				break;
			}
			tmp = curr;
			curr = curr->next;
		}
		i++;
	}
	return (0);
}
