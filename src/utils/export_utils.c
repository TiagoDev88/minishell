/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:26:31 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/16 23:05:43 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../includes/parser.h"

/**
 * @brief Adds a new environment variable to the list.
 *
 * Parses the given string and splits it into key and value.
 * Supports both standard `key=value` and `key+=value` syntax.
 * If there is no `=`, only the key is added.
 *
 * @param envp The string containing the full export argument.
 * @param env_list Pointer to the environment list.
 * @param new Flag indicating mode:
 *  - 1 for normal assignment,
 *  - 2 for `+=` concatenation.
 */
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

/**
 * @brief Updates the value of an existing environment variable.
 *
 * Parses the value from the input string and either replaces or appends to 
 * the existing value depending on the mode.
 *
 * @param envp The full input string containing key=value.
 * @param node Pointer to the environment variable to update.
 * @param conc Flag indicating the operation:
 *  - 1 to replace,
 *  - 2 to concatenate (`+=`).
 */
static void	update_export_env(char *envp, t_envp **node, int conc)
{
	char	*value;
	char	*equal;
	char	*tmp;

	equal = ft_strchr(envp, '=');
	if (!equal || !node)
		return ;
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
 * @brief Adds or updates an environment variable based on input.
 *
 * Checks if the given key already exists in the list.
 * If it does, the value is updated or concatenated depending on the syntax.
 * If not, a new variable is added.
 *
 * @param arg The export argument (e.g., VAR=value or VAR+=value).
 * @param envp Pointer to the environment list.
 * @param k_stats The key status from `valid_key()`:
 *  - 1 to update,
 *  - 2 to concatenate (`+=`).
 */
void	is_update_or_add_env(char *arg, t_envp **envp, int k_stats)
{
	int		k_len;
	t_envp	*tmp_envp;
	int		updated;

	tmp_envp = *envp;
	updated = 0;
	while (tmp_envp)
	{
		k_len = ft_strlen(tmp_envp->key);
		if (!ft_strncmp(tmp_envp->key, arg, k_len)
			&& (arg[k_len] == '=' || arg[k_len] == '+' || arg[k_len] == '\0'))
		{
			update_export_env(arg, &tmp_envp, k_stats);
			updated = 1;
			return ;
		}
		tmp_envp = tmp_envp->next;
	}
	if (updated == 0)
		add_export_env(arg, envp, k_stats);
}
