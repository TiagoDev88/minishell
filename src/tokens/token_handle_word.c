#include "../includes/minishell.h"


//TODO tratar do erro das quotes nao terem pares
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
        printf("Erro: aspa não fechada, tenho que dar ERRO porque nao encontrou o par de quots\n");
        return (1);
    }
    return (0);
}

//TODO verificar as alocacoes
// e se part vem NULL
static void	word_append(char **word, char *part)
{
	char	*tmp;

	if (!*word)
		*word = part;
	else
	{
		tmp = ft_strjoin(*word, part);
		free(*word);
		free(part);
		if (!tmp)
			return ;
		*word = tmp;
	}
}
//TODO tratar de diminuir linhas, usando outras funcoes auxiliares.
//verificar alocacoes no codigo.
// part pode vir NULL
void handle_word(t_token **tokens, t_token_builder *bd)
{
    char *word;
    char *part;
    int start;
    int res;

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
        word_append(&word, part);
        res = check_state(bd);
        if (res == 1)
            break;
    }
    add_token(tokens, new_token(TOKEN_WORD, word));
}
