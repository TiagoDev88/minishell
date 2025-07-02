#ifndef BUILTINS_H
# define BUILTINS_H

# include "parser.h"

int ft_echo(t_cmd *cmd);
int ft_exit(t_cmd **cmd);
int ft_cd(t_cmd *cmd);
int	ft_env(t_cmd *cmd, t_envp *envp);

#endif