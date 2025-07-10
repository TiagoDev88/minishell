/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:03:50 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/10 12:10:19 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static char	*get_envp(char *envp_to_get, t_exec *exec, char *cmd)
{
	char	*envp;

	envp = getenv(envp_to_get);
	if (!envp)
		print_cmd_err_exit(cmd, 1, 127, exec);
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
	int		i;
	char	*path;

	i = 0;
	while (path_split[i])
	{
		path = build_cmd_path(path_split[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0 && ft_strcmp("..", cmd) != 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	if (!path)
		print_cmd_err_exit(cmd, 0, 127, exec);
	if (access(path, X_OK) != 0)
	{
		free(path);
		print_cmd_err_exit(cmd, 0, 126, exec);
	}
	return (path);
}

static char	*get_path_from_curr_dir(t_exec *exec, char *cmd)
{
	char	*curr_dir;
	char	*cmd_path;

	curr_dir = get_envp("PWD", exec, cmd);
	if (!curr_dir)
		return (NULL);
	cmd_path = build_cmd_path(curr_dir, cmd);
	if (!cmd_path)
		return (NULL);
	if (access(cmd_path, F_OK) != 0)
	{
		free(cmd_path);
		print_cmd_err_exit(cmd, 1, 127, exec);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		free(cmd_path);
		print_cmd_err_exit(cmd, 1, 126, exec);
	}
	return (cmd_path);
}

char	*get_cmd_path(t_exec *exec, char *cmd)
{
	char	*path_envp;
	char	**path_split;
	char	*cmd_path;

	if (cmd[0] == '.' && cmd[1] == '/')
		cmd_path = get_path_from_curr_dir(exec, cmd);
	else
	{
		path_envp = get_envp("PATH", exec, cmd);
		if (!path_envp)
			return (NULL);
		path_split = ft_split(path_envp, ':');
		free(path_envp);
		if (!path_split)
			return (NULL);
		cmd_path = get_path_from_path_env(exec, path_split, cmd);
		cmd_clean_split(path_split, 0);
	}
	if (!cmd_path)
	{
		print_error_msg(NULL, strerror(ENOMEM), 1);
		exit_clean(exec, ENOMEM);
	}
	return (cmd_path);
}
