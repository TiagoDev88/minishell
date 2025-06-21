/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:54:10 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/21 20:00:50 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/token.h"

void	clean_split(char **split)
{
	int	i;

	if (!(*split))
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	*split = NULL;
}

int	clean_cmds(t_cmd **lst, int status)
{
	t_cmd	*curr;
	t_cmd	*tmp;

	curr = *lst;
	while (curr)
	{
		clean_split(curr->cmd);
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	return (status);
}

int clean(void *p1, void *p2, void *p3, int status)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p3);
	return (status);
}

char	*safe_join(char *join, char *to_join, t_token *token, int flag)
{
	char *temp;

	if (!join || !to_join || !token)
		return (NULL);
	// Verify token sep_by_space FLAG
	// If sep_by_space = 1
	if (flag)
	{
		temp = join;
		join = ft_strjoin(join, " ");
		if (!join)
		{
			free(temp);
			return (NULL);
		}
		free(temp);
	}
	// Point temp to join
	temp = join;
	// Call strjoin to join (*join + *to_join)
	join = ft_strjoin(join, to_join);
	// Free temp
	free(temp);
	return (join);
} 

int	is_cmd(t_token *prev)
{
	if (!prev)
	{
		printf("PREV IS NULL\n");
		return (1);
	}
	if (prev->type == TOKEN_PIPE)
	{
		printf("PREV IS NULL2\n");
		return (1);
	}
	return (0);
}

void add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*curr;

	if (!new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		curr = *lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

t_cmd *create_node(void)
{
	t_cmd *new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	ft_memset(new, 0, sizeof(t_cmd));
	return (new);
}

int	build(t_cmd **lst, t_token **curr)
{
	t_cmd	*new;
	t_token *prev;
	char	*clean_cmd;

	new = create_node();
	if (!new)
		return (0);
	prev = NULL;
	while (*curr && (*curr)->type == TOKEN_WORD)
	{
		if (!prev) // Quer dizer que é o primeiro comando.
			clean_cmd = ft_strdup((*curr)->value);
		else
			clean_cmd = safe_join(clean_cmd, (*curr)->value, *curr, 1);
		if (!clean_cmd)
			return (0);
		prev = *curr;
		*curr = (*curr)->next;
	}
	new->cmd = ft_split(clean_cmd, ' ');
	if (!new->cmd)
		return (clean(clean_cmd, NULL, NULL, 0));
	add_back(lst, new);
	return (clean(clean_cmd, NULL, NULL, 1));
}

// Percorre os TOKENS TODOS e forma uma lista linkada de comandos ou um ARRAY
// Para ter um array, o ideal seria fazer a contagem de comandos na formatacao dos tokens.
int build_cmds(t_cmd **lst, t_token *head)
{
	t_token	*curr;
	t_token *prev;

	curr = head;
	prev = NULL;
	while (curr)
	{
		if (curr->type == TOKEN_WORD)
			if (is_cmd(prev))
				if (!build(lst, &curr))
					return (clean_cmds(lst, 0));
		if (curr)
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (1);
}
