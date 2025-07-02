/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:02:34 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/02 23:15:27 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

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
