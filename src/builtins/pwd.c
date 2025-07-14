
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

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
