#include "../includes/minishell.h"


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

