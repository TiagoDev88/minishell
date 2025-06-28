#include "../includes/minishell.h"

//TODO: depois tenho que ver como vou tratar do exit status
// vai ser com a variavel global, o EXIT CODE

int signal_code = 35; // vai ser para teste, depois tenho que tratar
static char *extract_variable(t_token_builder *bd)
{
    char var[256];
    int j;
    char *value;

    j = 0;
    bd->pos++;
    var[0] = '\0';
    if (bd->input[bd->pos] == '?')
    {
        bd->pos++;
        return (ft_itoa(signal_code)); // substituir $? pelo exit status (exemplo fixo 10)
    }
    while (bd->input[bd->pos] && (ft_isalpha(bd->input[bd->pos]) || bd->input[bd->pos] == '_'))
    {
        var[j] = bd->input[bd->pos];
        j++;
        bd->pos++;
    }
    var[j] = '\0';
    value = getenv(var);
    if (!value)
        return (ft_strdup(""));
    return (ft_strdup(value));
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

static void	append_text(t_token_builder **bd, char **part, int *start)
{
	char	*tmp;
	char	*env_val;

	tmp = ft_substr((*bd)->input, *start, (*bd)->pos - *start);
	if (!tmp)
		return ;
	env_val = ft_strjoin(*part, tmp);
	if (!env_val)
	{
		free(tmp);
		return ;
	}
	free(*part);
	free(tmp);
	*part = env_val;
}

int	append_dollar(t_token_builder **bd, char **part, int *start, int flag)
{
	char	*tmp;
	char	*env_val;

	if ((*bd)->pos > *start)
		append_text(bd, part, start);
	if (flag == 1)
	{
		env_val = extract_variable((*bd));
		if (!env_val)
			return (0);
		tmp = ft_strjoin(*part, env_val);
		if (!tmp)
		{
			free(env_val);
			return (0);
		}
		free(*part);
		free(env_val);
		*part = tmp;
		*start = (*bd)->pos;
	}
	return (1);
}

int	check_dollar_cases(t_token_builder **bd, char **part, int *start)
{
	char next;

	if ((*bd)->input[(*bd)->pos] == '$')
	{
		next = (*bd)->input[(*bd)->pos + 1];
		if (next == '\0' || next == ' ' || ft_strchr("\"\'\t><|", next))
		{
			(*bd)->pos++;
			return (2);
		}
		if (is_ignored_variable(bd, start))
			return (1);
		if ((*bd)->del != '\'')
		{
			append_dollar(bd, part, start, 1);
			return (1);
		}
	}
	return (0);
}

