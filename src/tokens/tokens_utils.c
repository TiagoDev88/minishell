

#include "../includes/minishell.h"

t_token	*new_token(t_token_type type, const char *value)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tk, t_token *new)
{
	t_token	*tmp;

	if (!*tk)
	{
		*tk = new;
		return;
	}
	tmp = *tk;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_tokens(t_token **tk)
{
	t_token	*tmp;
	t_token *ptr;

	if (tk == NULL || *tk == NULL)
		return;
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
