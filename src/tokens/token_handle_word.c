#include "../includes/token.h"

static char *extract_word(char *input, int start, int *i, int del)
{
	// reparar se vem com flag = 1 para expandir as variaveis.
	char *part;
	while (input[*i])
		{
			if (del != ' ')
			{
				if (input[*i] == del)
					break ;
			}
			else
			{
				if (input[*i] == del)
					break ;
			}
			(*i)++;
		}
		part = ft_substr(input, start, *i - start);
		return (part);
}


void	handle_word(t_token **tokens, char *input, int *i, char del)
{
	char	*word;
	char *tmp;
	char	*part;
	int		start;
	int flag;
	word = NULL;
	tmp = NULL;
	flag = 0;
	if (del == '"')
		flag = 1;
	while (input[*i])
	{
		if (del == ' ')
		{
			if (input[*i] == '\'' || input[*i] == '"')
			{
				del = input[*i];
				(*i)++;
			}
		}
		start = *i;
		part = extract_word(input, start, i, del);
		if (!word)
			word = part;
		else
		{
			tmp = word;
			word = ft_strjoin(word, part);
			free(tmp);
			free(part);
		}
		printf("%c\n", input[*i]);
		printf("%s\n", word);
		if (del != ' ' && input[*i] == del)
		{
			(*i)++;
			del = ' ';
		}
		else if (del == ' ')
		{
			if (input[*i] == ' ' )
			break ;
			if (input[*i] == '\'' || input[*i] == '"')
			{
				del = input[*i];
				(*i)++;
			}
			else
			break ;
		}
	}
	add_token(tokens, new_token(TOKEN_WORD, word, flag));
}

// Se ainda não estamos dentro de quotes e encontramos uma marcamos o delimitador
// Se terminou numa quote sai do delimitador antigo
// Se encontramos um separador fora de aspas vamos parar a leitura
// Se encontramos outra quotecontinuamos a ler
// Se tiver flag 1 de " tenho que tratar por causa da expansao das variaveis
// Tratar diretamente aqui, se nao tem par de quotes, para dar erro.