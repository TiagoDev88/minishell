/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:26:31 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/14 02:15:50 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../includes/parser.h"

static void	add_export_env(char *envp, t_envp **env_list, int new)
{
	char	*key;
	char	*value;
	char	*equal;
	int		key_len;

	if (new == 2)
		equal = ft_strnstr(envp, "+=", ft_strlen(envp));
	else
		equal = ft_strchr(envp, '=');
	if (equal)
	{
		key_len = equal - envp;
		key = ft_substr(envp, 0, key_len);
		if (new == 2)
			value = ft_strdup(equal + 2);
		else
			value = ft_strdup(equal + 1);
		add_envp(env_list, new_envp(key, '=', value));
	}
	else
	{
		key = ft_strdup(envp);
		add_envp(env_list, new_envp(key, 0, NULL));
	}
	assign_indexes(*env_list);
}


static void	update_export_env(char *envp, t_envp **node, int conc)
{
	char	*value;
	char	*equal;
	int		key_len;
	char	*tmp;

	equal = ft_strchr(envp, '=');
	if (!equal || !node)
		return ;
	key_len = equal - envp;
	value = ft_strdup(equal + 1);
	if (conc == 2 && (*node)->value != NULL)
	{
		tmp = ft_strjoin((*node)->value, value);
		free((*node)->value);
		(*node)->value = tmp;
	}
	else
	{
		free((*node)->value);
		(*node)->value = value;
	}
	(*node)->flag = '=';
}

/**
 * @brief Updates an existing environment variable or adds a new one.
 *
 * Searches through the environment variable list to find a match for the given key.
 * If found and the key is valid, the value is updated (or concatenated if using '+=' syntax).
 * If not found and the key is valid, a new variable is created and added to the list.
 *
 * @param arg      The input string containing key=value or key+=value.
 * @param envp     Double pointer to the environment variable list.
 * @param k_stats  Key status returned from valid_key: 1 = update, 2 = concatenate.
 */
void is_update_or_add_env(char *arg, t_envp **envp, int k_stats)
{
	int		key_len;
	t_envp	*tmp_envp;
	int updated;

	tmp_envp = *envp;
	updated = 0;
	while (tmp_envp)
	{
		key_len = ft_strlen(tmp_envp->key);
		if (!ft_strncmp(tmp_envp->key, arg, key_len) &&
			(arg[key_len] == '=' || arg[key_len] == '+' || arg[key_len] == '\0'))
		{
			update_export_env(arg, &tmp_envp, k_stats);
			updated = 1;
			return;
		}
		tmp_envp = tmp_envp->next;
	}
	if (updated == 0)
		add_export_env(arg, envp, k_stats);
}

