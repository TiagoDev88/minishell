/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:19:36 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/19 15:19:37 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

/**
 * @brief Removes the first node in the environment list if it
 *  matches the given key.
 * 
 * Compares the provided key with the first node's key. If they
 *  match, the first node 
 * is removed from the linked list and its memory is freed.
 * 
 * @param cmd_env The key of the environment variable to unset.
 * @param envp Double pointer to the head of the environment variable list.
 * 
 * @return Returns 1 if the first node was removed, 0 otherwise.
 */
static int	unset_first_envp(char *cmd_env, t_envp **envp)
{
	t_envp	*head;

	head = *envp;
	if (!ft_strncmp(cmd_env, head->key, ft_strlen(head->key)))
	{
		*envp = head->next;
		free(head->key);
		if (head->value)
			free(head->value);
		free(head);
		return (1);
	}
	return (0);
}

/**
 * @brief Removes a non-first environment variable node that 
 * matches the given key.
 * 
 * Iterates through the linked list starting from the second 
 * node to find and remove 
 * a node whose key matches the provided key. Frees the node's memory.
 * 
 * @param cmd_env The key of the environment variable to unset.
 * @param envp Double pointer to the current node's pointer
 *  (not the head of the list).
 */
static void	unset_next_envp(char *cmd_env, t_envp **envp)
{
	t_envp	*curr;
	t_envp	*tmp;

	curr = *envp;
	while (curr)
	{
		if (!ft_strncmp(cmd_env, curr->key, ft_strlen(curr->key)))
		{
			tmp->next = curr->next;
			free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			break ;
		}
		tmp = curr;
		curr = curr->next;
	}
}

/**
 * @brief Implements the builtin `unset` command to remove
 *  environment variables.
 * 
 * Iterates through the arguments passed to the `unset` command
 *  and removes matching
 * environment variable nodes from the linked list. Handles the special case of 
 * removing the first node separately.
 * 
 * @param cmd Pointer to the command structure containing arguments.
 * @param envp Double pointer to the environment variables linked list.
 * 
 * @return Returns 0 on success, or 1 if input is invalid or if the
 *  environment is empty.
 */
int	ft_unset(t_cmd *cmd, t_envp **envp)
{
	t_envp	*curr;
	int		i;

	if (!cmd || !envp || !*envp)
		return (1);
	i = 1;
	while (cmd->cmd_args[i])
	{
		if (unset_first_envp(cmd->cmd_args[i], envp))
			continue ;
		curr = (*envp)->next;
		unset_next_envp(cmd->cmd_args[i], &curr);
		i++;
	}
	return (0);
}
