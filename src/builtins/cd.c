
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

static char	*get_oldpwd(t_envp *envp)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD", envp);
	if (!oldpwd || oldpwd[0] == '\0')
		return (ft_putstr_fd("bash: cd: OLDPWD not set\n", 2), NULL);
	ft_putendl_fd(oldpwd, 1);
	return (ft_strdup(oldpwd));
}

static int	update_pwd_and_oldpwd(t_envp **envp)
{
	char	*oldpwd;
	char	*pwd;
	char	*cwd;
	char	*check_oldpwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	check_oldpwd = get_env_value("OLDPWD", *envp);
	oldpwd = ft_strjoin("OLDPWD=", get_env_value("PWD", *envp));
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!oldpwd || !pwd)
		return (free(oldpwd), free(pwd), 1);
	is_update_or_add_env(oldpwd, envp, 0);
	is_update_or_add_env(pwd, envp, 0);
	free(oldpwd);
	free(pwd);
	return (0);
}

char	*get_home_path(char *arg, t_envp *envp)
{
	char	*home;
	char	*result;

	home = get_env_value("HOME", envp);
	if (!home)
		return (ft_putstr_fd("bash: cd: HOME not set\n", 2), NULL);
	if (!arg || arg[0] == '\0' || (arg[0] == '~' && arg[1] == '\0'))
		return (ft_strdup(home));
	if (arg[0] == '~' && arg[1] == '/')
	{
		result = ft_strjoin(home, arg + 1);
		return (result);
	}
	return (ft_strdup(arg));
}

int	ft_cd(t_cmd *cmd, t_envp *envp, t_shell *shell)
{
	char	*path;

	if (!cmd || !cmd->cmd_args || !envp)
		return (1);
	if (cmd->cmd_args[2])
		return (ft_putstr_fd("bash: cd: too many arguments\n", 2), 1);
	if (!cmd->cmd_args[1] || cmd->cmd_args[1][0] == '~')
		path = get_home_path(cmd->cmd_args[1], envp);
	else if (ft_strncmp(cmd->cmd_args[1], "-", 2) == 0)
		path = get_oldpwd(envp);
	else
		path = ft_strdup(cmd->cmd_args[1]);
	if (!path)
		return (1);
	if (chdir(path) != 0)
		return (ft_putstr_fd("bash: cd: ", 2), perror(path), free(path), 1);
	free(path);
	update_pwd_and_oldpwd(&shell->envp);
	return (0);
}
