#include "../includes/token.h"

static t_token	*new_token(t_token_type type, const char *value, int flag)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->double_quote = flag;
	token->sep_by_space = -1;
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

	//depois tratar single quotes e double quotes (FLAG)
	//fazer uma verificacao se e ' ou "
static void	handle_word(t_token **tokens, char *input, int *i, char del)
{
	int	start;
	int flag;
	t_token *new;
	char *token;

	flag = 0;

	start = *i;
	while (input[*i])
	{
		if (input[*i] == del)
			break;
		(*i)++;
	}
	if (del == '"')
		flag = 1; // new->double_quotes = 1;
	add_token(tokens, new_token(TOKEN_WORD, ft_substr(input, start, *i - start), flag));
	if (input[*i] == del) // Paramos em cima do delimitador e andamos para a frente.
		(*i)++;
	else
	{
		if (del == '\'' || del == '"')
			printf("QUOTES UNCLOSED\n");
		// Nao terminou com delimitador = ' ou "
		// Retornar erro e limpar.
	}
	// Se a seguir ao delimitador for igual a espaco
	if (input[*i] == ' ')
		// mudar flag para quando houver concatencao, separar com espaco
		// new->sep_space = 1;

}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;
	char del;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		printf("input: %s INDEX: %i\n", input + i, i);
		del = ' ';
		while (input[i] == del || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		if (!ft_strncmp(&input[i], ">>", 2) || !ft_strncmp(&input[i], "<<", 2))
		{
			add_token(&tokens, new_token(get_token_type(&input[i]), ft_substr(input, i, 2), 0));
			i += 2;
		}
		else if (ft_strchr("> < |", input[i]))
		{
    		add_token(&tokens, new_token(get_token_type(&input[i]), ft_substr(input, i, 1), 0));
    		i++;
		}
		else
		{
			printf("IS WORD\n");
			if (input[i] == '\"' || input[i] == '\'')
			{
				del = input[i];
				i++;
			}
			// {
			// 	handle_word(&tokens, input, &i);
			// }
			// else
			handle_word(&tokens, input, &i, del);
		}
		//printf("Fim dentro do primeiro while");
		if (i == 15)
			break;
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
