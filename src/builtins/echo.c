/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:00:08 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/01 16:42:01 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
//TODO resolver estes testes 
// echo -n -n -nnnn -nnnnm
// echo -n
// echo ola

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (cmd->cmd_args[i] && ft_strncmp(cmd->cmd_args[i], "-n", 3) == 0)
	{
		nl = 0;
		i++;
	}
	while (cmd->cmd_args[i])
	{
		printf("%s", cmd->cmd_args[i]);
		if (cmd->cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}
