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
	char			*filename;
	int				unlink;
	struct s_file	*next;
}	t_file;

typedef struct s_files_container
{
	int		last_out_fd;
	int		last_in_fd;
	int		heredocs;
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


extern int EXIT_STATUS;

/* Main */
void	execute(t_token *tokens, t_cmd *cmd_lst, char **envp);
/* Path */
char	*get_cmd_path(t_exec *exec, char *cmd);
/* File */
//int		add_file(t_files_container *files_container, char *filename, int redir_type);
void	add_file_back(t_file **file_lst, t_file *new_file);
int		open_files(t_token **curr_token, t_exec *exec);
void	clean_files(t_file **file_lst);
void	close_files(t_files_container *files_container);
t_file	*create_file_node(void);

/* Proccess */
void	exec_cmd(char *cmd_path, t_exec *exec, t_cmd *cmd, char **envp);
void	handle_redirects(t_exec *exec);
/* Cleaner */
void	exit_clean(t_exec *exec, int exit_status);
int		clean_mem(void *p1, void *p2, void *p3, int exit_status);
int		return_clean(t_exec *exec, char *error, int exit_status);
/* Error */
void	print_error_msg(char *cmd, char *error, int mode);
void	print_cmd_err_and_exit(char *cmd, int mode, int exit_status, t_exec *exec);
int		print_file_err_and_return(char *filename, char *error, int exit_status);
/* Heredoc */
int	heredoc(t_file **new_file, char *delimiter, t_files_container **files_container);

#endif