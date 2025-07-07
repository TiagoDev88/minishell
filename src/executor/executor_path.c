/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:03:50 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/07 12:57:10 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_envp(char *envp_to_get, t_exec *exec, char *cmd)
{
	char	*envp;

	envp = getenv(envp_to_get);
	if (!envp)
		print_cmd_err_and_exit(cmd, 1, 127, exec);
	return (ft_strdup(envp));
}

static char	*build_cmd_path(char *dir, char *cmd)
{
	char	*tmp_dir;
	char	*cmd_dir;

	if (!dir || !cmd)
		return (NULL);
	tmp_dir = ft_strjoin(dir, "/");
	if (!tmp_dir)
		return (NULL);
	cmd_dir = ft_strjoin(tmp_dir, cmd);
	free(tmp_dir);
	return (cmd_dir);
}

static char	*get_path_from_path_env(t_exec *exec, char **path_split, char *cmd)
{
	int i;
	char *path;

	i = 0;
	while (path_splitted[i])
	{
		path = build_cmd_path(path_splitted[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	if (access(path, F_OK) != 0)
	{
		free(path);
		print_cmd_err_and_exit(cmd, 0, 127, exec);
	}
	else if (access(path, X_OK) != 0)
	{
		free(path);
		print_cmd_err_and_exit(cmd, 0, 126, exec);
	}
	return (NULL);
}

static char	*get_path_from_curr_dir(t_exec *exec, char *cmd)
{
	char *curr_dir;
	char *cmd_path;

	curr_dir = get_envp("PWD", exec, cmd);
	if (!curr_dir)
		return (NULL);
	cmd_path = build_cmd_path(curr_dir, cmd);
	if (!cmd_path)
		return (NULL);
	if (access(cmd_path, F_OK) != 0)
	{
		free(cmd_path);
		print_cmd_err_and_exit(cmd, 1, 127, exec);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		free(cmd_path);
		print_cmd_err_and_exit(cmd, 1, 126, exec);
	}
	return (cmd_path);
}

char	*get_cmd_path(t_exec *exec, char *cmd)
{
	char *path_envp;
	char **path_splitted;
	char *cmd_path;

	if (cmd[0] == '.')
		cmd_path = get_path_from_curr_dir(exec, cmd);
	else
	{
		path_envp = get_envp("PATH", exec, cmd);
		if (!path_envp)
			return (NULL);
		path_splitted = ft_split(path_envp, ':');
		free(path_envp);
		if (!path_splitted)
			return (NULL);
		cmd_path = get_path_from_path_envp(exec, path_splitted, cmd);
	}
	if (!cmd_path)
	{
		cmd_clean_split(path_splitted, 0);
		print_error_msg(NULL, strerror(ENOMEM), 1);
		exit_clean(exec, ENOMEM);
	}
	cmd_clean_split(path_splitted, 0);
	return (cmd_path);
}
