#ifndef UTILS_H
# define UTILS_H

# include "parser.h"


typedef struct s_envp
{
	char *key;
	char flag;
	char *value;
	int	index;
	struct s_envp *next;
} t_envp;

t_envp *new_envp(char *key, char flag, char *value);
void add_envp(t_envp **envp, t_envp *new);
void free_envp(t_envp **);
void	copy_env(char **envp, t_envp **env_list);
void print_export_envp(t_envp *envp); // chamar a funcao de printar.
void assign_indexes(t_envp *env_list);
char *get_env_value(char *name, t_envp **lst_envp);
void is_update_or_add_env(char *arg, t_envp **envp, int k_stats);


#endif