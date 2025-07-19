/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:19:12 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/19 15:19:13 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

/**
 * @brief Retrieves the value of OLDPWD environment variable.
 * 
 * Prints an error and returns NULL if OLDPWD is not set or empty.
 * Otherwise, prints the value to stdout and returns a duplicate of it.
 * 
 * @param envp The environment variable linked list.
 * @return char* Duplicate of OLDPWD value or NULL if unset.
 */
static char	*get_oldpwd(t_envp *envp)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD", envp);
	if (!oldpwd || oldpwd[0] == '\0')
		return (ft_putstr_fd("bash: cd: OLDPWD not set\n", 2), NULL);
	ft_putendl_fd(oldpwd, 1);
	return (ft_strdup(oldpwd));
}

/**
 * @brief Updates the PWD and OLDPWD environment variables after changing
 *  directory.
 * 
 * Retrieves current working directory and updates OLDPWD to previous PWD,
 * then updates PWD to the current directory.
 * Returns 0 on success, 1 on failure.
 * 
 * @param envp Double pointer to the environment list.
 * @return int 0 on success, 1 on failure.
 */
static int	update_pwd_and_oldpwd(t_envp **envp)
{
	char	*oldpwd;
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	oldpwd = ft_strjoin("OLDPWD=", get_env_value("PWD", *envp));
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!oldpwd || !pwd)
		return (free(oldpwd), free(pwd), 1);
	is_update_or_add_env(oldpwd, envp, 0);
	is_update_or_add_env(pwd, envp, 0);
	free(oldpwd);
	free(pwd);
	return (0);
}

/**
 * @brief Resolves the home path for the cd command.
 * 
 * If arg is NULL, empty, or "~", returns HOME environment variable value.
 * If arg starts with ~/, replaces ~ with HOME and appends the rest.
 * Otherwise, returns a duplicate of arg.
 * Prints error and returns NULL if HOME is unset.
 * 
 * @param arg The argument to cd.
 * @param envp The environment linked list.
 * @return char* The resolved path or NULL on error.
 */
char	*get_home_path(char *arg, t_envp *envp)
{
	char	*home;
	char	*result;

	home = get_env_value("HOME", envp);
	if (!home)
		return (ft_putstr_fd("bash: cd: HOME not set\n", 2), NULL);
	if (!arg || arg[0] == '\0' || (arg[0] == '~' && arg[1] == '\0'))
		return (ft_strdup(home));
	if (arg[0] == '~' && arg[1] == '/')
	{
		result = ft_strjoin(home, arg + 1);
		return (result);
	}
	return (ft_strdup(arg));
}

/**
 * @brief Executes the cd builtin command.
 * 
 * Handles zero, one, or two arguments (errors on more than one argument).
 * Resolves the path, changing to HOME if no argument or "~".
 * Supports "cd -" to change to OLDPWD.
 * Prints errors for invalid paths or too many arguments.
 * Updates PWD and OLDPWD environment variables on success.
 * 
 * @param cmd The command struct with arguments.
 * @param envp The environment variables list.
 * @param shell The shell context.
 * @return int 0 on success, 1 on failure.
 */
int	ft_cd(t_cmd *cmd, t_envp *envp, t_shell *shell)
{
	char	*path;

	if (!cmd || !cmd->cmd_args || !envp)
		return (1);
	if (cmd->cmd_args[1] && cmd->cmd_args[2])
		return (ft_putstr_fd("bash: cd: too many arguments\n", 2), 1);
	if (!cmd->cmd_args[1] || cmd->cmd_args[1][0] == '~')
		path = get_home_path(cmd->cmd_args[1], envp);
	else if (ft_strncmp(cmd->cmd_args[1], "-", 2) == 0)
		path = get_oldpwd(envp);
	else
		path = ft_strdup(cmd->cmd_args[1]);
	if (!path)
		return (1);
	if (chdir(path) != 0)
		return (ft_putstr_fd("bash: cd: ", 2), perror(path), free(path), 1);
	free(path);
	update_pwd_and_oldpwd(&shell->envp);
	return (0);
}
