
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"


/**
 * @brief Validates whether a given string is a valid export key.
 *
 * This function checks if the key part of a variable assignment is valid
 * according to shell naming rules. It also detects if the syntax includes '+='.
 *
 * @param cmd  The raw export argument string (e.g., "VAR=value" or "VAR+=value").
 * @return int Returns 0 if invalid, 1 if valid for update/definition, 2 if using '+=' syntax.
 */
static int valid_key(char *cmd)
{
	int	i;

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

/**
 * @brief Handles the export command logic in the minishell.
 *
 * This function processes the export command arguments. If no arguments are provided,
 * it prints the environment variables in sorted format. Otherwise, it validates each
 * argument and attempts to either update an existing variable or add a new one.
 *
 * @param cmd   Pointer to the parsed command structure containing arguments.
 * @param envp  Double pointer to the environment variable linked list.
 * @return int  Returns 0 on success, 1 if an error occurs (e.g., invalid input).
 */
int	ft_export(t_cmd *cmd, t_envp **envp)
{
	if (!cmd || !envp|| !(*envp))
		return (1);
	if (cmd->cmd_args[1] == NULL)
		return (print_export_envp(*envp), 0);
	int		i;
	int		key_status;

	i = 1;
	while (cmd->cmd_args[i])
	{
		key_status = valid_key(cmd->cmd_args[i]);
		if (key_status == 0)
		{
			ft_putstr_fd("bash: export: `", 2);
       		ft_putstr_fd(cmd->cmd_args[i], 2);
        	ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_status = 1;
			i++;
			continue;
		}
		is_update_or_add_env(cmd->cmd_args[i], envp, key_status);
		i++;
	}
	return (g_exit_status);
}
