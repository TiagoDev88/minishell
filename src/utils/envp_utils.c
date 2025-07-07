/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:03:39 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/07 11:20:29 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

t_envp *new_envp(char *key, char flag, char *value)
{
	t_envp *new_envp;

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
void	add_envp(t_envp **envp, t_envp *new)
{
	t_envp *tmp;
	
	if (!*envp)
	{
		*envp = new;
		return;
	}
	tmp = *envp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

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

static void	util_print_export_envp(t_envp *envp, int size)
{
	t_envp *tmp;
	int i;

	tmp = envp;
	i = 0;
	while (i < size)
	{
		tmp = envp;
		while (tmp)
		{
			if (tmp->index == i && tmp->key[0] != '_')
			{
				if (tmp->flag == '=')
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
				else
					printf("declare -x %s\n", tmp->key);
				break;
			}
			tmp = tmp->next;
		}
		i++;
	}
}

void print_export_envp(t_envp *envp)
{
	t_envp *tmp;
	int i;
	int size;

	assign_indexes(envp);
	tmp = envp;
	i = 0;
	size = 0;
	while(tmp)
	{
		size++;
		tmp = tmp->next;
	}
	util_print_export_envp(envp, size);
}
