/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:03:39 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/03 11:01:56 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void print_envp(t_envp *envp)
{
	printf("dentro do print_envp\n");
	printf("envp-> %s\n", envp->key);
}