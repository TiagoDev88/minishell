//TODO tratar destes casos
// no builtin CD (ele atualiza duas ENV, o PWD e o OLDPWD, 
// nas variaveis de ambiente. o PWD, e onde esta, e o OLDPWD e onde estava)

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

//TODO falta atualizar o OLDPWD e o PWD
// usar talvez o getcwd para uma estrutura t_envp ou outra e chamar aqui para atualizar
// testar com por exemplo cd ~/path/



// int ft_cd(t_cmd *cmd, t_envp *envp, t_shell *shell)
// {
//     char *path;
//     int i;

//     printf("comando   %s\n", cmd->cmd_args[0]);

//     if (!cmd || !cmd->cmd_args || !envp)
//         return (1);
//     i = 1;
//     if (!cmd->cmd_args[1] || cmd->cmd_args[1][0] == '~')
//     {
//         path = get_env_value("HOME", envp);
//         if (!path)
//             return (ft_putstr_fd("bash: cd: HOME not set\n", 2), 1);
//         if (cmd->cmd_args[1][1] == '/')
//             path = ft_strjoin(path, &cmd->cmd_args[1][1]);
//         //printf("comando para o pwd com path %s\n", path);
//     }
//     // if (cmd->cmd_args[i][1] !=)
//     else if (ft_strncmp(cmd->cmd_args[1], "-", 2) == 0)
//     {
//         path = get_env_value("OLDPWD", envp);
//         printf("%s\n", path);
//         if (!path)
//             return (ft_putstr_fd("bash: cd: OLDPWD not set\n", 2), 1);// TRATAR DISTO, PORQUE AQUI FICA O OLDPWD
//     }
//     else
//         path = cmd->cmd_args[1];
//     printf("path antes do chdir %s\n", path);
//     if (chdir(path) != 0)
//     {
//         ft_putstr_fd("bash: cd: ", 2);
//         ft_putstr_fd(path, 2);
//         ft_putstr_fd(": ", 2);
//         perror("");
//         return (1);
//     }
//     // free(shell->pwd);
//     // shell->pwd = getcwd(NULL, 0);
//     // shell->pwd = ft_strjoin("PWD=", shell->pwd);
//     // //shell->oldpwd[ft_strlen(shell->oldpwd - 1)] = '\0';
//     // shell->oldpwd = ft_strjoin("OLDPWD=", shell->oldpwd);

//     // is_update_or_add_env(shell->oldpwd, &envp, 0);
//     // is_update_or_add_env(shell->pwd, &envp, 0);

//     // if (path)
//     // {
//     //     path = getcwd(NULL, 0);
//     //     printf("com getwc%s\n", path);
//     //     path = ft_strjoin("PWD=", path);
//     //     printf("%s\n", path);
//     //     is_update_or_add_env(path, envp, 0);
//     // }
//     return (0);
// }


static char	*get_oldpwd(t_envp *envp)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD", envp);
    printf("get oldpwd %s\n", oldpwd);

	if (!oldpwd || oldpwd[0] == '\0')
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		return (NULL);
	}
	ft_putendl_fd(oldpwd, 1);
	return (ft_strdup(oldpwd));
}

static int	update_pwd_and_oldpwd(t_envp **envp)
{
	char	*oldpwd;
	char	*pwd;
	char	*cwd;
    char    *check_oldpwd;

    cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
    check_oldpwd = get_env_value("OLDPWD", *envp);
    printf("check oldpwd %s\n", check_oldpwd);
    oldpwd = ft_strjoin("OLDPWD=", get_env_value("PWD", *envp));
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!oldpwd || !pwd)
		return (free(oldpwd), free(pwd), 1);
    printf("oldpwd %s\n", oldpwd);


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
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (NULL);
	}
	if (!arg || arg[0] == '\0' || (arg[0] == '~' && arg[1] == '\0'))
		return (ft_strdup(home));
	if (arg[0] == '~' && arg[1] == '/')
	{
		result = ft_strjoin(home, arg + 1);
		return (result);
	}
	return (ft_strdup(arg));
}

int ft_cd(t_cmd *cmd, t_envp *envp, t_shell *shell)
{
	char	*path;

	if (!cmd || !cmd->cmd_args || !envp)
		return (1);
	if (!cmd->cmd_args[1] || cmd->cmd_args[1][0] == '~')
		path = get_home_path(cmd->cmd_args[1], envp);
	else if (ft_strncmp(cmd->cmd_args[1], "-", 2) == 0)
		path = get_oldpwd(envp);
	else
		path = ft_strdup(cmd->cmd_args[1]);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		perror(path);
		free(path);
		return (1);
	}
	free(path);
	update_pwd_and_oldpwd(&shell->envp);
	return (0);
}
