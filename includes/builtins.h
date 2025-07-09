#ifndef BUILTINS_H
# define BUILTINS_H

# include "parser.h"

typedef struct s_shell t_shell;

int ft_echo(t_cmd *cmd);
int ft_exit(t_cmd **cmd);
int ft_cd(t_cmd *cmd, t_envp **envp, t_shell *shell);
int	ft_env(t_cmd *cmd, t_envp *envp);
int ft_export(t_cmd *cmd, t_envp **envp);

#endif