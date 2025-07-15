#include "../../includes/minishell.h"

/**
 * @brief Checks if the given command is a shell built-in.
 * 
 * Returns 1 if cmd is one of the built-ins 
 * (cd, echo, env, exit, export, pwd, unset)
 * and does not contain a '/' character. Returns 0 otherwise.
 * 
 * @param cmd Command string to check.
 * @return int 1 if built-in, 0 if not.
 */
int	is_built_in(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (0);
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "unset"));
}

/**
 * @brief Checks if the given token is a redirection token.
 * 
 * Assumes token types are defined so that redirections
 * have types between TOKEN_REDIR_OUT and TOKEN_HEREDOC inclusive.
 * 
 * @param token Pointer to the token to check.
 * @return int 1 if token is a redirection, 0 otherwise.
 */
int	is_redirect(t_token *token)
{
	return (token->type >= TOKEN_REDIR_OUT && token->type <= TOKEN_HEREDOC);
}

/**
 * @brief Adds or updates the environment variable for last command (_=value).
 * 
 * Concatenates "_=" with the given value, then calls
 * is_update_or_add_env to add or update it in the shell environment list.
 * If allocation fails, exits cleanly with ENOMEM.
 * 
 * @param shell Pointer to the shell structure.
 * @param last_cmd_env Pointer to the environment node for the last command
 *  (may be NULL).
 * @param lcenv_val Value string to set for the last command.
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
 * @brief Updates the last command environment variable (_=...) 
 * based on the command executed.
 * 
 * If the command contains a '/', uses cmd_path as value.
 * If it is a built-in, uses the last argument of cmd_args as value.
 * Otherwise, uses cmd_path.
 * Frees and replaces the value if the environment node exists,
 * or adds a new one if not.
 * Exits cleanly if memory allocation fails.
 * 
 * @param shell Pointer to the shell structure.
 * @param last_cmd_env Pointer to the environment node for the last 
 * command (may be NULL).
 * @param cmd Pointer to the command structure executed.
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
 * @brief Searches for an environment variable node by key.
 * 
 * Iterates the environment linked list and returns the node
 * whose key matches the given string envp.
 * 
 * @param envp Key string to search for.
 * @param lst_envp Head of the environment variable linked list.
 * @return t_envp* Pointer to the matching node or NULL if not found.
 */
t_envp	*get_envp_node(char *envp, t_envp *lst_envp)
{
	t_envp	*curr;

	curr = lst_envp;
	while (curr && ft_strcmp(curr->key, envp))
		curr = curr->next;
	return (curr);
}
