#include "../../includes/minishell.h"

int	is_built_in(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (0);
	return (!ft_strcmp(cmd, "cd") ||
			!ft_strcmp(cmd, "echo") ||
			!ft_strcmp(cmd, "env") ||
			!ft_strcmp(cmd, "exit") ||
			!ft_strcmp(cmd, "export") ||
			!ft_strcmp(cmd, "pwd") ||
			!ft_strcmp(cmd, "unset"));
}

int	is_redirect(t_token *token)
{
	return (token->type >= TOKEN_REDIR_OUT && token->type <= TOKEN_HEREDOC);
}

void	add_last_cmd_env(t_shell *shell, t_envp *last_cmd_env, char *lcenv_val)
{
	char	*key_value;

	key_value = ft_strjoin("_=", lcenv_val);
	if (!key_value)
		exit_clean(shell, ENOMEM);
	is_update_or_add_env(key_value, &shell->envp, 1);
}

// void	update_last_cmd_env(t_shell *shell, t_envp *last_cmd_env, t_cmd *cmd)
// {
// 	char	*lc_env_value;
// 	int		i;

// 	if (ft_strchr(cmd->cmd_args[0], '/'))
// 		lc_env_value = ft_strdup(cmd->cmd_path);
// 	else if (is_built_in(cmd->cmd_args[0]))
// 	{
// 		i = 0;
// 		while (cmd->cmd_args[i + 1])
// 			i++;
// 		lc_env_value = ft_strdup(cmd->cmd_args[i]);
// 	}
// 	else
// 		lc_env_value = ft_strdup(cmd->cmd_path);
// 	if (!lc_env_value)
// 		exit_clean(shell, ENOMEM);
// 	if (last_cmd_env)
// 	{
// 		free(last_cmd_env->value);
// 		last_cmd_env->value = lc_env_value;
// 	}
// 	else
// 		add_last_cmd_env(shell, last_cmd_env, lc_env_value);
// }

void	update_last_cmd_env(t_shell *shell, t_envp *last_cmd_env, t_cmd *cmd)
{
	char	*lc_env_value;
	int		i;

	i = 0;
	if (ft_strchr(cmd->cmd_args[0], '/'))
		lc_env_value = ft_strdup(cmd->cmd_path);
	else if (is_built_in(cmd->cmd_args[0]))
	{
		while (cmd->cmd_args[i + 1])
			i++;
		lc_env_value = ft_strdup(cmd->cmd_args[i]);
	}
	else
	{
		if (cmd->cmd_args[i + 1] != NULL)
		{
			while (cmd->cmd_args[i + 1])
				i++;
			lc_env_value = ft_strdup(cmd->cmd_args[i]);
		}
		else
			lc_env_value = ft_strdup(cmd->cmd_path);	
	}
	if (!lc_env_value)
		exit_clean(shell, ENOMEM);
	if (last_cmd_env)
	{
		free(last_cmd_env->value);
		last_cmd_env->value = lc_env_value;
	}
	else
		add_last_cmd_env(shell, last_cmd_env, lc_env_value);
}

t_envp *get_envp_node(char *envp, t_envp *lst_envp)
{
	t_envp	*curr;

	curr = lst_envp;
	while (curr && ft_strcmp(curr->key, envp))
		curr = curr->next;
	return (curr);
}
