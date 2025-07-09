#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include "../includes/libft/libft.h"
# include "token.h"
# include "executor.h"
# include "builtins.h"
# include "parser.h"
# include "utils.h"


typedef struct s_shell
{
	t_envp **envp;
	t_cmd *cmd;
	char *oldpwd;
	char *pwd;
	char *underscore;
	int last_status_code;
} t_shell;

#endif