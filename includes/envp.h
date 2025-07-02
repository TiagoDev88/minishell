#ifndef ENVP_H
#define ENVP_H

typedef struct s_envp
{
	char *key;
	char flag;
	char *value;
	struct s_envp *next;
} t_envp;

t_envp *new_envp(char *key, char flag, char *value);
void add_envp(t_envp **envp, t_envp *new);
void free_envp(t_envp **);
void copy_env(char **envp);
#endif