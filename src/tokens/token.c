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


t_token	*tokenize(char *input, char **envp)
{
	t_token_builder	bd;
	t_token			*tk;
	char *substr;

	bd.input = input;
	bd.envp = envp;
	bd.pos = 0;
	bd.del = ' ';
	tk = NULL;

	while (bd.input[bd.pos])
	{
		bd.del = ' ';
		while (bd.input[bd.pos] == ' ' || bd.input[bd.pos] == '\t')
			bd.pos++;
		if (!bd.input[bd.pos])
			break ;
		if (!ft_strncmp(&bd.input[bd.pos], ">>", 2) || !ft_strncmp(&bd.input[bd.pos], "<<", 2))
		{
			substr = ft_substr(bd.input, bd.pos, 2);
            if (!substr)
                break;
			add_token(&tk, new_token(get_token_type(&bd.input[bd.pos]), substr));
			free(substr);
			bd.pos += 2;
		}
		else if (ft_strchr("> < |", bd.input[bd.pos]))
		{
			substr = ft_substr(bd.input, bd.pos, 1);
            if (!substr)
                break;
			add_token(&tk, new_token(get_token_type(&bd.input[bd.pos]), substr));
			free(substr);
			bd.pos++;
		}
		else
		{
			if ((bd.input[bd.pos] == '\"' || bd.input[bd.pos] == '\'') && bd.input[bd.pos + 1])
			{
				bd.del = bd.input[bd.pos];
				bd.pos++;
			}
			handle_word(&tk, &bd);
		}
	}
	return (tk);
}

void	free_tokens(t_token *tk)
{
	t_token	*tmp;

	while (tk)
	{
		tmp = tk;
		tk = tk->next;
		free(tmp->value);
		free(tmp);
	}
}

/*

new test: $$ = placehold for current pid number.

bash-5.2$ echo $$"ola $USER"
2023ola tfilipe-

bash-5.2$ echo $$"ola $USE"
2023ola 

bash-5.2$ echo $$"ola $"
2023ola $

bash-5.2$ echo $$"ola $$"
2023ola 2023

bash-5.2$ echo $$"ola $$" $$
2023ola 2023 2023

bash-5.2$ echo $$"ola $$" $
2023ola 2023 $

bash-5.2$ echo $$"ola $$"$
2023ola 2023$

bash-5.2$ echo $$"ola $$" $
2023ola 2023 $

bash-5.2$ echo $$ "ola $$" $
2023 ola 2023 $

bash-5.2$ echo $"ola"
ola

bash-5.2$ echo $$"ola"
2023ola

bash-5.2$ echo $$ "ola"
2023 ola

bash-5.2$ echo $$ "ola $"
2023 ola $

bash-5.2$ echo $$ "ola $" $
2023 ola $ $

bash-5.2$ echo $$ "ola $"$
2023 ola $$

bash-5.2$ echo $$ "ola $"$ $$
2023 ola $$ 2023

bash-5.2$ echo $$ "ola $USER"$ $$
2023 ola tfilipe-$ 2023

bash-5.2$ echo $$ "ola $invalid"$ $$
2023 ola $ 2023

bash-5.2$ echo $$ "ola $invalid" $ $$
2023 ola  $ 2023


*/
