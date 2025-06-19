#include "../includes/token.h"

static t_token	*new_token(t_token_type type, const char *value)
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

static void	add_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!*tokens)
	{
		*tokens = new;
		return;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}


static t_token_type	get_token_type(const char *s)
{
	if (!ft_strncmp(s, ">>", 2))
		return (TOKEN_APPEND);
	if (!ft_strncmp(s, "<<", 2))
		return (TOKEN_HEREDOC);
	if (*s == '>')
		return (TOKEN_REDIR_OUT);
	if (*s == '<')
		return (TOKEN_REDIR_IN);
	if (*s == '|')
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}

static void	handle_word(t_token **tokens, char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && !ft_strchr(" \t > < |", input[*i]))
		(*i)++;
	add_token(tokens, new_token(TOKEN_WORD, ft_substr(input, start, *i - start)));
}


t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		if (!ft_strncmp(&input[i], ">>", 2) || !ft_strncmp(&input[i], "<<", 2))
		{
			add_token(&tokens, new_token(get_token_type(&input[i]), ft_substr(input, i, 2)));
			i += 2;
		}
		else if (ft_strchr("> < |", input[i]))
		{
    		add_token(&tokens, new_token(get_token_type(&input[i]), ft_substr(input, i, 1)));
    		i++;
		}
		else
			handle_word(&tokens, input, &i);
	}
	return (tokens);
}


void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}
