//TODO tratar destes casos
// no builtin CD (ele atualiza duas ENV, o PWD e o OLDPWD, 
// nas variaveis de ambiente. o PWD, e onde esta, e o OLDPWD e onde estava)

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

//TODO falta atualizar o OLDPWD e o PWD
// usar talvez o getcwd para uma estrutura t_envp ou outra e chamar aqui para atualizar
// testar com por exemplo cd ~/path/
int ft_cd(t_cmd *cmd, t_envp **envp, t_shell *shell)
{
    char *path;

    if (shell->oldpwd)
        free(shell->oldpwd);
    shell->oldpwd = shell->pwd;
    printf("OLDPWD: %s\n", shell->oldpwd);

    if (!cmd || !cmd->cmd_args || !envp || !*envp || !shell)
        return (1);
    if (!cmd->cmd_args[1] || cmd->cmd_args[1][0] == '~')
    {
        path = get_env_value("HOME", envp);
        if (!path)
            return (ft_putstr_fd("bash: cd: HOME not set\n", 2), 1);
        if (cmd->cmd_args[1][1] != '\0')
            path = ft_strjoin(path, &cmd->cmd_args[1][1]);
        printf("comando para o pwd com path %s\n", path);
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
    printf("path antes do chdir %s\n", path);
    if (chdir(path) != 0)
    {
        ft_putstr_fd("bash: cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        perror("");
        return (1);
    }
    free(shell->pwd);
    shell->pwd = getcwd(NULL, 0);
    shell->pwd = ft_strjoin("PWD=", shell->pwd);
    //shell->oldpwd[ft_strlen(shell->oldpwd - 1)] = '\0';
    shell->oldpwd = ft_strjoin("OLDPWD=", shell->oldpwd);

    is_update_or_add_env(shell->oldpwd, envp, 0);
    is_update_or_add_env(shell->pwd, envp, 0);

    // if (path)
    // {
    //     path = getcwd(NULL, 0);
    //     printf("com getwc%s\n", path);
    //     path = ft_strjoin("PWD=", path);
    //     printf("%s\n", path);
    //     is_update_or_add_env(path, envp, 0);
    // }
    return (0);
}

// static char *build_env_path(char *dir, char *cmd)
// {
//     char    *tmp_dir;
//     char    *cmd_dir;
//     if (!dir || !cmd)
//         return (NULL);
//     tmp_dir = ft_strjoin(dir, "/");
//     if (!tmp_dir)
//         return (NULL);
//     cmd_dir = ft_strjoin(tmp_dir, cmd);
//     free(tmp_dir);
//     return (cmd_dir);
// }

// int ft_cd(t_shell *ss)
// {
//     char *path;
//     t_shell *sh;

//     sh = ss;

//     // if (!sh || !*sh->envp)
//     //     return (1);
//     printf("sh: %s e sh->envp %s\n", sh, *sh->envp);
//     if (sh->oldpwd)
//     {
//         free(sh->oldpwd);
//         sh->oldpwd = sh->pwd;
//     }
//     if (!sh->cmd->cmd_args[1] || sh->cmd->cmd_args[1][0] == '~')
//     {
//         path = get_env_value("HOME", sh->envp);
//         printf("comando para o pwd %s\n", path);
//         if (!path)
//              return (ft_putstr_fd("bash: cd: HOME not set\n", 2), 1);
//         if (sh->cmd->cmd_args[1][1] != '\0')
//             //path = ft_strjoin(path, (sh->cmd->cmd_args[1] + 1));
//         printf("comando para o pwd com path %s\n", path);
//     }
//     else
//         path = sh->cmd->cmd_args[1];
//     if (chdir(path) != 0)
//     {
//         ft_putstr_fd("bash: cd: ", 2);
//         ft_putstr_fd(path, 2);
//         ft_putstr_fd(": ", 2);
//         perror("");
//         return (1);
//      }
//     return (0);
// }
