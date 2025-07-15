/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:49:01 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/15 16:44:13 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

/**
 * @brief Creates a new token with the given type and value.
 *
 * Allocates memory for a new token, sets its type and value,
 * and initializes the next pointer to NULL.
 *
 * @param type Type of the token (e.g., WORD, PIPE, REDIR).
 * @param value String value associated with the token.
 * @return Pointer to the new token, or NULL if allocation fails.
 */
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

/**
 * @brief Appends a token to the end of a token list.
 *
 * If the list is empty, it sets the new token as the head.
 * Otherwise, it traverses to the end and adds the new token.
 *
 * @param tk Pointer to the head of the token list.
 * @param new Token to append.
 */
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

/**
 * @brief Frees all tokens in the list and their associated values.
 *
 * Iterates through the list, frees each token's value and the token itself.
 * Sets the list pointer to NULL after cleanup.
 *
 * @param tk Pointer to the head of the token list.
 */
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
