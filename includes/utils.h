/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:16:27 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/19 15:16:27 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parser.h"

typedef struct s_envp
{
	char			*key;
	char			flag;
	char			*value;
	int				index;
	struct s_envp	*next;
}	t_envp;

t_envp	*new_envp(char *key, char flag, char *value);
void	add_envp(t_envp **envp, t_envp *new);
void	free_envp(t_envp **envp);
void	copy_env(char **envp, t_envp **env_list);
void	print_export_envp(t_envp *envp);
void	assign_indexes(t_envp *env_list);
char	*get_env_value(char *name, t_envp *lst_envp);
void	is_update_or_add_env(char *arg, t_envp **envp, int k_stats);
t_envp	*get_envp_node(char *envp, t_envp *lst_envp);

int		is_built_in(char *cmd);
int		is_redirect(t_token *token);
void	update_last_cmd_env(t_shell *shell, t_envp *last_cmd_env, t_cmd *cmd);

#endif