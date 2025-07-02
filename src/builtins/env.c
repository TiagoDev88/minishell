/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:02:34 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/02 15:54:50 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static char *get_env_value(char *name, char **envp)
// {
//     int i;
//     int len;

//     len = ft_strlen(name);
//     i = 0;
//     while (envp[i])
//     {
//         //printf("ENV: %s posicao %i\n", envp[i], i);
//         if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
//             return (ft_strdup(envp[i] + len + 1));
//         i++;
//     }
//     return (ft_strdup(""));
// }

void copy_env(char **envp)
{
	int i;
	char *value;
	char *key;
	size_t len;
	size_t len2;
	//int j;

	if (!envp || !*envp)
		return ;
	i = 0;
	while (envp[i])
	{
		//value = NULL;
		key = NULL;
		printf("entrou\n");
		len = ft_strlen(envp[i]);
		printf("LEN %ld\n", len);
		printf("%d\n", i);
		// key = ft_split(envp[i], '=');
		key = ft_strchr(envp[i], '=');
		printf("%s\n", key);
		len = len - ft_strlen(key);
		printf("LEN da key %ld\n", len);
		//key = ft_strlcpy(key, envp[i], len);
		len2 = ft_strlcat(key, envp[i], len);
		printf("depois da copia %s\n", key);
		printf("LEN2 da key %ld\n", len2);
		if (!ft_strncmp(envp[i], key, len) && envp[i][len] == '=')
			value = ft_strdup(envp[i] + len + 1);
		// printf("%s", key);
		printf("%s\n", value);
		// value = ft_split(envp[i], envp[i][j]);
		// printf("key[%d]: %s valor[%d]: %s\n", envp[i], key, envp[i], value);
		// add_envp(envp[i], new_envp(key, '=', value));
		i++;
		if (i > 10)
			break;
	}
}

//usar split para guardar as keys e os valores