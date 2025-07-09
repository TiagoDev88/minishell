//TODO tratar destes casos
// no builtin CD (ele atualiza duas ENV, o PWD e o OLDPWD, 
// nas variaveis de ambiente. o PWD, e onde esta, e o OLDPWD e onde estava)

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

//TODO falta atualizar o OLDPWD e o PWD
// usar talvez o getcwd para uma estrutura t_envp ou outra e chamar aqui para atualizar
// testar com por exemplo cd ~/path/ ou cd -/path/ acho que era assim.
int ft_cd(t_cmd *cmd, t_envp **envp)
{
    char *path;

    if (!cmd || !cmd->cmd_args)
        return (1);
    if (!cmd->cmd_args[1] || (cmd->cmd_args[1][0] == '~' && cmd->cmd_args[1][1] == '\0'))
    {
        path = get_env_value("HOME", envp);
        if (!path)
            return (ft_putstr_fd("bash: cd: HOME not set\n", 2), 1);
    }
    else if (ft_strncmp(cmd->cmd_args[1], "-", 2) == 0)
    {
        path = get_env_value("OLDPWD", envp);
        printf("%s\n", path);
        if (!path)
            return (ft_putstr_fd("bash: cd: OLDPWD not set\n", 2), 1);// TRATAR DISTO, PORQUE AQUI FICA O OLDPWD
    }
    else
        path = cmd->cmd_args[1];
    if (chdir(path) != 0)
    {
        ft_putstr_fd("bash: cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        perror("");
        return (1);
    }
    if (path)
    {
        path = getcwd(NULL, 0);
        printf("com getwc%s\n", path);
        path = ft_strjoin("PWD=", path);
        printf("%s\n", path);
        is_update_or_add_env(path, envp, 0);
    }
    return (0);
}
