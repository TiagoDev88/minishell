#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef	struct s_proccess
{
	pid_t				pid;
	struct s_proccess	*next;
}	t_proccess;

typedef struct s_file
{
	int				fd;
	struct s_file	*next;
}	t_file;

typedef struct s_files_container
{
	int		last_out_fd;
	int		last_in_fd;
	t_file	*lst;
}	t_files_container;

typedef struct s_pipe
{
	int				write_fd;
	int				read_fd;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_exec
{
	t_proccess			*procc_lst;
	t_files_container	files_container;
	t_pipe				*pipe_lst;
}	t_exec;

/* Main */
void	execute(t_token *tokens, t_cmd *cmd_lst, char **envp);
/* Path */
char	*get_cmd_path(char *cmd);
/* File */
int		open_files(t_token **curr_token, t_files_container *files_container);
void	close_files(t_files_container *files_container);
/* Proccess */
void	exec_cmd(char *cmd_path, t_cmd *cmd, char **envp);
void	handle_redirects(t_files_container *files_container);
/* Cleaner */
void	exit_clean(t_exec *exec, char *error, int exit_status);

#endif