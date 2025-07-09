/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:49:01 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/01 10:26:33 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tk, t_token *new)
{
	t_token	*tmp;

	if (!*tk)
	{
		*tk = new;
		return ;
	}
	tmp = *tk;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_tokens(t_token **tk)
{
	t_token	*tmp;
	t_token	*ptr;

	if (tk == NULL || *tk == NULL)
		return ;
	ptr = *tk;
	while (ptr != NULL)
	{
		tmp = ptr->next;
		free(ptr->value);
		free(ptr);
		ptr = tmp;
	}
	*tk = NULL;
}
