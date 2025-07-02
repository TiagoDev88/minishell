/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:41:05 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/02 20:58:37 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	copy_env(char **envp, t_envp **env_list)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal;
	int		key_len;

	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			key_len = equal - envp[i];
			key = ft_substr(envp[i], 0, key_len);
			value = ft_strdup(equal + 1);
			add_envp(env_list, new_envp(key, '=', value));
		}
		else
		{
			key = ft_strdup(envp[i]);
			add_envp(env_list, new_envp(key, 0, NULL));
		}
		i++;
	}
}
