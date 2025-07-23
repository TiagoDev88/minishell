/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:00:08 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/23 10:52:12 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

/**
 * @brief Checks if the argument is a valid '-n' flag.
 * 
 * Supports multiple 'n' characters after the dash,
 *  like '-n', '-nn', '-nnn', etc.
 * Returns 1 if the arg is a valid '-n' flag, 0 otherwise.
 * 
 * @param arg Argument string to check.
 * @return int 1 if valid '-n' flag, else 0.
 */
static int	n_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' && arg[i + 1] == 'n')
	{
		i += 2;
		while (arg[i] == 'n')
			i++;
		if (arg[i] == '\0')
			return (1);
	}
	return (0);
}

static void	help_echo(char *arg, t_envp *envp)
{
	char	*home_path;

	if (arg[0] == '~' && (arg[1] == '\0' || arg[1] == '/'))
	{
		home_path = get_home_path(arg, envp);
		printf("%s", home_path);
		free(home_path);
	}
	else
		printf("%s", arg);
}

/**
 * @brief Implementation of the echo builtin command.
 * 
 * Prints the arguments separated by spaces.
 * Supports '-n' flags that suppress the trailing newline.
 * Supports multiple '-n' flags in a row.
 * 
 * @param cmd Command struct containing arguments.
 * @return int Always returns 0.
 */
int	ft_echo(t_cmd *cmd, t_envp *envp)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (!cmd || !cmd->cmd_args || !cmd->cmd_args[0])
		return (1);
	while (cmd->cmd_args[i] && n_flag(cmd->cmd_args[i]))
	{
		nl = 0;
		i++;
	}
	while (cmd->cmd_args[i])
	{
		help_echo(cmd->cmd_args[i], envp);
		if (cmd->cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}
