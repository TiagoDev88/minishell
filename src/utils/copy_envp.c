/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:41:05 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/16 23:06:14 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Assigns a sorted index to each environment variable.
 *
 * This function compares all environment variable keys in the list and assigns
 * each node an index corresponding to its alphabetical position (ASCII order).
 * 
 * This index can be used to print the `export` list in sorted order without 
 * altering the original list structure.
 *
 * @param env_list Linked list of environment variables.
 */
void	assign_indexes(t_envp *env_list)
{
	t_envp	*current_node;
	t_envp	*others_node;
	int		index;

	if (!env_list)
		return ;
	current_node = env_list;
	while (current_node)
	{
		index = 0;
		others_node = env_list;
		while (others_node)
		{
			if (ft_strcmp(current_node->key, others_node->key) > 0)
				index++;
			others_node = others_node->next;
		}
		current_node->index = index;
		current_node = current_node->next;
	}
}

/**
 * @brief Builds a linked list from the environment variables array.
 *
 * This function takes each string from the original `envp` array and splits it 
 * into key and value pairs. If the string contains `'='`, the key and value
 *  are separated accordingly. If not, only the key is stored and the value
 *  is set to NULL. After processing the full array, it calls `assign_indexes`
 *  to compute the sort index of each variable.
 * 
 * @param envp Environment array received from main.
 * @param env_list Pointer to the linked list of environment variables.
 */
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
	assign_indexes(*env_list);
}

/**
 * @brief Retrieves the value of an environment variable by its name.
 *
 * Searches the environment list for a node with a matching key and flag `'='`.
 * If found, returns a newly allocated copy of its value.
 *
 * @param name The name of the environment variable to search for.
 * @param lst_envp The environment list to search in.
 * @return A newly allocated string with the variable value, or
 *  NULL if not found.
 */
char	*get_env_value(char *name, t_envp *lst_envp)
{
	int		i;
	t_envp	*envp;

	envp = lst_envp;
	i = 0;
	while (envp)
	{
		if (!ft_strcmp(envp->key, name) && envp->flag == '=')
			return (ft_strdup(envp->value));
		envp = envp->next;
		i++;
	}
	return (NULL);
}
