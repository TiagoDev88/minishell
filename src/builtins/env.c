/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:02:34 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/06 17:55:49 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

/**
 * @brief Prints the environment variables.
 * This function iterates through the linked list of environment variables
 * 
 * and prints each variable in the format "key=value".
 * If a variable has no value, it prints "key=".
 * if the variable has a flag of '=', it is printed.
 * else it is skipped.
 * * @param cmd Pointer to the command structure (not used in this function).
 * @param envp Pointer to the linked list of environment variables.
 * * @return Returns 0 on success, or 1 if cmd or envp is NULL.
 * * @note This function assumes that the environment variables are stored
 * 
 */
int	ft_env(t_cmd *cmd, t_envp *envp)
{
	if (!cmd || !envp)
		return (1);
	t_envp *tmp;
	
	tmp = envp;
	while (tmp)
	{
		if (tmp->flag == '=')
		{
			if (tmp->value)
				printf("%s=%s\n", tmp->key, tmp->value);
			else
				printf("%s=\n", tmp->key);
		}
		tmp = tmp->next;
	}
	return (0);
}
