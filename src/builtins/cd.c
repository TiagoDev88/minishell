//TODO tratar destes casos
// no builtin CD (ele atualiza duas ENV, o PWD e o OLDPWD, 
// nas variaveis de ambiente. o PWD, e onde esta, e o OLDPWD e onde estava)

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
//TODO talvez vou ter problemas por causa dos ENVS. Tenho que fazer uma copia dos ENVS
int ft_cd(t_cmd *cmd)
{
    char *path;

    if (!cmd || !cmd->cmd_args)
        return (1);
    if (!cmd->cmd_args[1] || cmd->cmd_args[1][0] == '~')
    {
        path = getenv("HOME");
        if (!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return (1);
        }
    }
    else
        path = cmd->cmd_args[1];

    if (chdir(path) != 0)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        perror("");
        return (1);
    }
    return (0);
}
