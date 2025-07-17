/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:03:39 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/17 10:40:43 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Creates a new environment variable node.
 * 
 * Allocates and initializes a new t_envp structure with the given key,
 *  flag, and value.
 * The index is initialized to -1, and next pointer to NULL.
 * 
 * @param key The key/name of the environment variable (ownership transferred).
 * @param flag Character indicating if variable has a value 
 * ('=' if yes, 0 if no).
 * @param value The value of the environment variable 
 * (ownership transferred, can be NULL).
 * @return Pointer to the newly created t_envp struct or NULL on malloc 
 * failure.
 */
t_envp	*new_envp(char *key, char flag, char *value)
{
	t_envp	*new_envp;

	new_envp = malloc(sizeof(t_envp));
	if (!new_envp)
		return (NULL);
	new_envp->key = key;
	new_envp->flag = flag;
	new_envp->value = value;
	new_envp->index = -1;
	new_envp->next = NULL;
	return (new_envp);
}

/**
 * @brief Adds a new environment variable node to the end of the list.
 * 
 * If the list is empty, sets the new node as the head.
 * Otherwise, iterates to the last node and appends the new node.
 * 
 * @param envp Pointer to the head of the environment variable list.
 * @param new The new node to be added.
 */
void	add_envp(t_envp **envp, t_envp *new)
{
	t_envp	*tmp;

	if (!*envp)
	{
		*envp = new;
		return ;
	}
	tmp = *envp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/**
 * @brief Frees the entire environment variable list.
 * 
 * Iterates through the list, freeing key, value, and the node itself.
 * Sets the original pointer to NULL to avoid dangling pointers.
 * 
 * @param envp Double pointer to the environment variable list head.
 */
void	free_envp(t_envp **envp)
{
	t_envp	*tmp;
	t_envp	*ptr;

	if (envp == NULL || *envp == NULL)
		return ;
	ptr = *envp;
	while (ptr != NULL)
	{
		tmp = ptr->next;
		free(ptr->value);
		free(ptr->key);
		free(ptr);
		ptr = tmp;
	}
	*envp = NULL;
}

/**
 * @brief Helper function to print environment variables sorted by index.
 * 
 * Iterates from index 0 to size-1 and prints the variable matching that index.
 * Skips the variable named "_" (underscore) with length 1 
 * (usually shell internal).
 * Prints in the format expected by `export` builtin:
 * - If variable has a value: declare -x key="value"
 * - If variable has no value: declare -x key
 * 
 * @param envp Head of the environment list.
 * @param size Number of variables in the list.
 */
static void	util_print_export_envp(t_envp *envp, int size)
{
	t_envp	*tmp;
	int		i;

	tmp = envp;
	i = 0;
	while (i < size)
	{
		tmp = envp;
		while (tmp)
		{
			if (tmp->index == i && (tmp->key[0] != '_' || tmp->key[1] != '\0'))
			{
				if (tmp->flag == '=')
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
				else
					printf("declare -x %s\n", tmp->key);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
}

/**
 * @brief Prints all environment variables sorted by their assigned index.
 * 
 * Calls assign_indexes() to update the sorting indexes, then prints the list.
 * 
 * @param envp Head of the environment variable list.
 */
void	print_export_envp(t_envp *envp)
{
	t_envp	*tmp;
	int		size;

	assign_indexes(envp);
	tmp = envp;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	util_print_export_envp(envp, size);
}
