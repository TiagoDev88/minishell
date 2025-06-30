/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_proccess.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:54:14 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/30 15:50:02 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(int redir_type, int fd)
{
	if (redir_type == 1)
	{
		if (fd != STDIN_FILENO)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		if (fd != STDOUT_FILENO)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
		}
	}
}

void	validate_cmd(char *cmd_path, t_exec *exec)
{
	struct stat sb;

	if (stat(cmd_path, &sb) != 0) // Verifica se o ficheiro existe.
		exit_clean(exec, "No such file or directory\n", 127);
	if (S_ISDIR(sb.st_mode)) // Verifica se é um diretorio
		exit_clean(exec, "Is a directory\n", 126);
	if (access(cmd_path, X_OK) != 0) // sem permissoes
		exit_clean(exec, "Permission denied\n", 126);
}


void	exec_cmd(char *cmd_path, t_exec *exec, t_cmd *cmd_lst, char **envp)
{
	if (!cmd_path)
		exit_clean(exec, "command not found\n", 127);
	validate_cmd(cmd_path, exec);
	execve(cmd_path, cmd_lst->cmd_args, envp);
	exit_clean(exec, "execve: error", EXIT_FAILURE);
}

void	handle_redirects(t_files_container *files_container)
{
	if (files_container->last_in_fd)
		redirect(1, files_container->last_in_fd);
	if (files_container->last_out_fd)
		redirect(2, files_container->last_out_fd);
}
