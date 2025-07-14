/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:41:05 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/14 13:36:29 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//TODO ordenar pela tabela ascii
//talvez usar o strncmp para verificar a diferenca nas palavras
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
			//printf("CURRENT node %s\n", current_node->key);
			if (ft_strcmp(current_node->key, others_node->key) > 0)
				index++;
			others_node = others_node->next;
		}
		current_node->index = index;
		//printf("KEY: %s com index %d\n", current_node->key, current_node->index);
		current_node = current_node->next;
	}
}

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

char *get_env_value(char *name, t_envp *lst_envp)
{
    int		i;
    int		len;
	t_envp	*envp;

	envp = lst_envp;
	len = ft_strlen(name);
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


