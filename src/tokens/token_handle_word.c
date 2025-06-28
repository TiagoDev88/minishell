#include "../includes/minishell.h"


//TODO tratar do erro das quotes nao terem pares
// talvez escrever o erro das quotes para o strerror
static int check_state(t_token_builder *bd)
{
    if (bd->del != ' ' && bd->input[bd->pos] == bd->del)
    {
        bd->pos++;
        bd->del = ' ';
        return (2);
    }
    if (bd->del == ' ' && ft_strchr("'\" \t><|", bd->input[bd->pos]))
    {
        if (bd->input[bd->pos] == '\'' || bd->input[bd->pos] == '"')
        {
            bd->del = bd->input[bd->pos];
            bd->pos++;
            return (2);
        }
        return (1);
    }
    if (bd->input[bd->pos] == '\0' && bd->del != ' ')
    {
        printf("minishell: syntax error: unclosed quote\n");
        return (-1);
    }
    return (0);
}

static int word_append(char **word, char *part)
{
    char *tmp;

    if (!*word)
    {
        *word = part;
        return (1);
    }
    tmp = ft_strjoin(*word, part);
    if (!tmp)
    {
        free(part);
        return (0);
    }
    free(*word);
    free(part);
    *word = tmp;
    return (1);
}

static char *extract_word(t_token_builder **bd, int start)
{
	char *part;
	int check;

	part = ft_strdup("");
	if (!part)
		return (NULL);
	while ((*bd)->input[(*bd)->pos])
	{
		check = check_dollar_cases(bd, &part, &start);
		if (check == 1)
			break;
		if (check == 2)
			continue;
		if ((*bd)->del != ' ' && (*bd)->input[(*bd)->pos] == (*bd)->del)
			break;
		if ((*bd)->del == ' ' && ft_strchr("\"$ '\t><|", (*bd)->input[(*bd)->pos]))
			break;
		(*bd)->pos++;
	}
	if ((*bd)->pos > start)
	{
		if (!append_dollar(bd, &part, &start, 0))
			return (free(part), NULL);
	}
	return (part);
}



//TODO tratar de diminuir linhas, usando outras funcoes auxiliares.
void handle_word(t_token **tokens, t_token_builder *bd)
{
	char	*word;
	char	*part;
	int		start;
	int		res;

	word = NULL;
	while (bd->input[bd->pos])
	{
		if (bd->del == ' ' && (bd->input[bd->pos] == '\'' || bd->input[bd->pos] == '"'))
		{
			bd->del = bd->input[bd->pos];
			bd->pos++;
		}
		start = bd->pos;
		part = extract_word(&bd, start);
		if (!part)
			return (free(word));
		if (!word_append(&word, part))
			return (free(word));
		res = check_state(bd);
		if (res == -1)
			return (free(word));
		if (res == 1)
			break;
	}
	if (word)
		add_token(tokens, new_token(TOKEN_WORD, word));
}

