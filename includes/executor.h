/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:25:05 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/07 22:13:37 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

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

typedef struct s_proccess
{
	pid_t				pid;
	struct s_proccess	*next;
}	t_proccess;

typedef struct s_exec_helper
{
	t_pipe	*last_pipe;
	int		exec_cmd;
	int		err_file;
}	t_exec_helper;

typedef struct s_exec
{
	t_proccess			*procc_lst;
	t_files_container	files_container;
	t_pipe				*pipe_lst;
	t_exec_helper		exec_h;
}	t_exec;

/* Main */
void		executor(t_token *tokens, t_cmd *cmd_lst, char **envp);
/* Cleaner */
void		close_pipes(t_pipe **pipe_lst);
void		exit_clean(t_exec *exec, int exit_s);
int			clean_mem(void *p1, void *p2, void *p3, int exit_s);
void		close_last_fds(t_exec *exec);
/* Command execution */
void		execute_command(t_exec *exec, t_cmd **curr_cmd, char **envp);
/* Error */
void		print_error_msg(char *cmd, char *error, int mode);
void		print_cmd_err_exit(char *cmd, int mode, int exit_s, t_exec *exec);
int			print_file_err(char *filename, char *error, int exit_s);
/* File struct */
void		clean_files_s(t_file **file_lst);
t_file		*create_file_node(void);
void		add_file_back(t_file **file_lst, t_file *new_file);
int			add_file(t_files_container *f_con, char *filename, int redir_type);
/* Heredoc */
int			heredoc(t_file **new, char *delimiter, t_files_container **f_con);
/* Path */
char		*get_cmd_path(t_exec *exec, char *cmd);
/* Pipes */
t_pipe		*handle_pipe(t_exec *exec, t_token **curr_token);
void		clean_pipe_s(t_pipe **pipe_lst);
/* Proccess struct */
t_proccess	*create_proccess(void);
void		procc_add_back(t_proccess **procc_lst, t_proccess *new_proccess);
void		clean_proccess_s(t_proccess **procc_lst);
/* Validator */
int			validate_and_open_files(t_token **curr_token, t_exec *exec);
int			has_cmd(t_token **curr);
void		validate_cmd(char *cmd_path, t_exec *exec);

#endif