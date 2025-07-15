#include "../../includes/minishell.h"

/**
 * is_built_in - Checks if a command is a built-in shell command.
 * @cmd: The command string to check.
 *
 * Returns 1 if the command is built-in, 0 otherwise.
 */
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

/**
 * is_redirect - Checks if a token represents a redirection operator.
 * @token: Pointer to the token to check.
 *
 * Returns 1 if the token is a redirection, 0 otherwise.
 */
int	is_redirect(t_token *token)
{
	return (token->type >= TOKEN_REDIR_OUT && token->type <= TOKEN_HEREDOC);
}

/**
 * add_last_cmd_env - Adds or updates the "_" environment variable.
 * @shell: Pointer to the shell structure.
 * @last_cmd_env: Pointer to the last command environment node (can be NULL).
 * @lcenv_val: The value to set for the "_" environment variable.
 *
 * Adds or updates the "_" environment variable with the given value.
 * Exits on memory allocation failure.
 */
void	add_last_cmd_env(t_shell *shell, t_envp *last_cmd_env, char *lcenv_val)
{
	char	*key_value;

	key_value = ft_strjoin("_=", lcenv_val);
	if (!key_value)
		exit_clean(shell, ENOMEM);
	is_update_or_add_env(key_value, &shell->envp, 1);
}

/**
 * update_last_cmd_env - Updates the "_" environment variable based on the last command.
 * @shell: Pointer to the shell structure.
 * @last_cmd_env: Pointer to the last command environment node (can be NULL).
 * @cmd: Pointer to the command structure.
 *
 * Sets the value of the "_" variable according to the last executed command.
 * Exits on memory allocation failure.
 */
void	update_last_cmd_env(t_shell *shell, t_envp *last_cmd_env, t_cmd *cmd)
{
	char	*lc_env_value;
	int		i;

	if (ft_strchr(cmd->cmd_args[0], '/'))
		lc_env_value = ft_strdup(cmd->cmd_path);
	else if (is_built_in(cmd->cmd_args[0]))
	{
		i = 0;
		while (cmd->cmd_args[i + 1])
			i++;
		lc_env_value = ft_strdup(cmd->cmd_args[i]);
	}
	else
		lc_env_value = ft_strdup(cmd->cmd_path);
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

/**
 * get_envp_node - Finds an environment variable node by key.
 * @envp: The key to search for (e.g., "_").
 * @lst_envp: Pointer to the head of the environment linked list.
 *
 * Returns a pointer to the matching environment node, or NULL if not found.
 */
t_envp *get_envp_node(char *envp, t_envp *lst_envp)
{
	t_envp	*curr;

	curr = lst_envp;
	while (curr && ft_strcmp(curr->key, envp))
		curr = curr->next;
	return (curr);
}
