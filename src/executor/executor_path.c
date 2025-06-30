/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:03:50 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/29 23:29:53 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_envp(void)
{
	char	*path_envp;

	path_envp = getenv("PATH");
	if (!path_envp)
		return (NULL);
	return (ft_strdup(path_envp));
}

static char	*build_path(char **path_splitted, char *cmd)
{
	int i;
	char *dir;
	char *path;

	i = 0;
	while (path_splitted[i])
	{
		dir = ft_strjoin(path_splitted[i], "/");
		if (!dir)
			return (NULL);
		path = ft_strjoin(dir, cmd);
		free(dir);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd)
{
	char *path_envp;
	char **path_splitted;
	char *cmd_path;

	if (!cmd)
		return (NULL);
	path_envp = get_path_envp();
	if (!path_envp)
		return (NULL);
	path_splitted = ft_split(path_envp, ':');
	if (!path_splitted)
		return (NULL);
	cmd_path = build_path(path_splitted, cmd);
	if (!cmd_path)
	{
		// Command not found
		return (NULL);
	}
	//printf("%s\n", cmd_path);
	//scheck_if_is_executable(char *cmd_path);
	return (cmd_path);
}
