/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:03:50 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/14 01:47:04 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_path_env_splitted(t_shell *shell, char *cmd)
{
	char	*path_envp;
	char	**path_split;

	path_envp = get_env_value("PATH", shell->envp);
	if (!path_envp)
	{
		print_cmd_err(cmd, 1, 127, shell);
		return (NULL);
	}
	path_split = ft_split(path_envp, ':');
	free(path_envp);
	if (!path_split)
		exit_clean(shell, ENOMEM);
	return (path_split);
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

static char	*get_path_from_path_env(t_shell *sh, char **path_split, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (path_split[i])
	{
		path = build_cmd_path(path_split[i], cmd);
		if (!path)
			exit_clean(sh, ENOMEM);
		if (access(path, F_OK) == 0 && ft_strcmp("..", cmd) != 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	cmd_clean_split(path_split, 0);
	if (!path)
		print_cmd_err(cmd, 0, 127, sh);
	else if (access(path, X_OK) != 0)
	{
		print_cmd_err(path, 1, 126, sh);
		free(path);
		path = NULL;
	}
	return (path);
}

static char	*get_path_from_curr_dir(t_shell *shell, char *cmd)
{
	char	*curr_dir;
	char	*cmd_path;

	curr_dir = get_env_value("PWD", shell->envp);
	if (!curr_dir)
	{
		print_cmd_err(cmd, 1, 127, shell);
		return (NULL);
	}
	cmd_path = build_cmd_path(curr_dir, cmd);
	if (!cmd_path)
		exit_clean(shell, ENOMEM);
	if (access(cmd_path, F_OK) != 0)
	{
		free(cmd_path);
		cmd_path = NULL;
		print_cmd_err(cmd, 1, 127, shell);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		free(cmd_path);
		cmd_path = NULL;
		print_cmd_err(cmd, 1, 126, shell);
	}
	return (cmd_path);
}

char	*get_cmd_path(t_shell *shell, char *cmd)
{
	char	**path_split;
	char	*cmd_path;

	if (!cmd[0])
	{
		print_cmd_err(cmd, 0, 127, shell);
		return (NULL);
	}
	if (cmd[0] == '.' && cmd[1] == '/')
		cmd_path = get_path_from_curr_dir(shell, cmd);
	else
	{
		path_split = get_path_env_splitted(shell, cmd);
		if (!path_split)
			return (NULL);
		cmd_path = get_path_from_path_env(shell, path_split, cmd);
	}
	return (cmd_path);
}
