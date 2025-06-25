#include "../includes/minishell.h"

//TODO retirar o printf
static char *get_env_value(char *name, char **envp)
{
    int i;
    int len;

    len = ft_strlen(name);
    i = 0;
    while (envp[i])
    {
        //printf("ENV: %s posicao %i\n", envp[i], i);
        if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
            return (ft_strdup(envp[i] + len + 1));
        i++;
    }
    return (ft_strdup(""));
}
//TODO: depois tenho que ver como vou tratar do exit status
// vai ser com a variavel global, o EXIT CODE

int signal_code = 35; // vai ser para teste, depois tenho que tratar
static char *extract_variable(t_token_builder *bd)
{
    char var[256];
    int j;
    char *value;

    j = 0;
    bd->pos++; // aqui vou saltar o '$'

    if (bd->input[bd->pos] == '?')
    {
        bd->pos++;
        return (ft_itoa(signal_code)); // substituir $? pelo exit status (exemplo fixo 10)
    }
    // as variaveis de ambiente $ tem que ser seguidas de letras ou _
    while (bd->input[bd->pos] && (ft_isalpha(bd->input[bd->pos]) || bd->input[bd->pos] == '_'))
    {
        var[j] = bd->input[bd->pos];
        j++;
        bd->pos++;
    }
    var[j] = '\0';
    value = get_env_value(var, bd->envp);
    if (!value)
        return (NULL);
    return (value);
}

static int	is_ignored_variable(t_token_builder **bd, int *start)
{
	if ((*bd)->input[(*bd)->pos + 1] == '\0')
	{
		(*bd)->pos++;
		return (1);
	}
	if (ft_isdigit((*bd)->input[(*bd)->pos + 1]))
	{
		(*bd)->pos += 2;
        *start = (*bd)->pos;
        return (0);
	}
	return (0);
}

//TODO talvez tratar com char* para nao andar so com endereco
// tratar das alocacoes
static void	append_dollar(t_token_builder **bd, char **part, int *start, int flag)
{
	char	*tmp;
	char	*env_val;

	if ((*bd)->pos > *start)
	{
		tmp = ft_substr((*bd)->input, *start, (*bd)->pos - *start);
		env_val = ft_strjoin(*part, tmp);
		free(*part);
		free(tmp);
		*part = env_val;
	}
    if (flag == 1)
    {
        env_val = extract_variable((*bd));
        tmp = ft_strjoin(*part, env_val);
        free(*part);
        free(env_val);
        *part = tmp;
        *start = (*bd)->pos;
    }
}

//TODO a flag vai servir para adicionar o que esta antes do $ com 1
// e 0 para juntar o resto da palavra que sobrou
// falta tratar deste teste $USER$USER deve imprimir duas variaveis seguidas.
char *extract_word(t_token_builder **bd, int start)
{
    char *part;

    part = ft_strdup("");
    if (!part)
        return (NULL);
    while ((*bd)->input[(*bd)->pos])
    {
		if ((*bd)->input[(*bd)->pos] == '$' && (*bd)->input[(*bd)->pos + 1] != ' ')
        {
            if (is_ignored_variable(bd, &start))
				break;
			if ((*bd)->del != '\'')
                append_dollar(bd, &part, &start, 1);
		}
        if ((*bd)->del != '\'' && (*bd)->input[(*bd)->pos] == '$')
            break;
        if ((*bd)->del != ' ' && (*bd)->input[(*bd)->pos] == (*bd)->del)
            break;
        if ((*bd)->del == ' ' && ft_strchr("\"$ '\t><|", (*bd)->input[(*bd)->pos]))
            break;
        (*bd)->pos++;
    }
    if ((*bd)->pos > start)
        append_dollar(bd, &part, &start, 0);
    return (part);
}
