
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

/**
 * @brief Implements the builtin `pwd` command to print the current
 *  working directory.
 * 
 * Retrieves the current working directory from the `PWD` environment variable.
 * If `PWD` is not set, it falls back to calling `getcwd()`.
 *  Then, it prints the path to stdout.
 * 
 * @param cmd Pointer to the current command structure
 *  (used for argument validation).
 * @param envp Pointer to the environment variable linked list.
 * 
 * @return Returns 0 on success, or 1 if an error occurs.
 */
int	ft_pwd(t_cmd *cmd, t_envp *envp)
{
	char	*pwd;

	if (!cmd->cmd_args || !cmd || !envp)
		return (1);
	pwd = get_env_value("PWD", envp);
	if (!pwd)
		pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	ft_putendl_fd(pwd, 1);
	return (0);
}
