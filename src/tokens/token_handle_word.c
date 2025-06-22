#include "../includes/token.h"


static char *extract_word(char *input, int start, int *i, int del)
{
	char	*part;

	while (input[*i])
	{
		if (del != ' ' && input[*i] == del)
			break ;
		if (del == ' ' && ft_strchr("\" '\t><|", input[*i]))
			break ;
		(*i)++;
	}
	part = ft_substr(input, start, *i - start);
	return (part);
}


static int	check_state(char *input, int *i, char *del)
{
	if (*del != ' ' && input[*i] == *del)
	{
		(*i)++;
		*del = ' ';
		return (2); // tem que continuar
	}
	if (*del == ' ' && ft_strchr("' \" \t><|", input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			*del = input[*i];
			(*i)++;	
			return (2); // tem que continuar
		}
		// printf("checkstate %d\n", *del);
		return (1); // para dar break
	}
	if (input[*i] == '\0' && *del != ' ')
	{
		printf("Erro: aspa não fechada, tenho que dar ERRO porque nao encontrou o par de quots\n");
		return (1); // para dar break
	}
	printf("checkstate printf final\n");
	return (0); // para prosseguir normalmente
}


void	handle_word(t_token **tokens, char *input, int *i, char del)
{
	char	*word;
	char *tmp;
	char	*part;
	int		start;
	int flag;
	int res;
	word = NULL;
	tmp = NULL;
	flag = 0;
	if (del == '"')
		flag = 1;
	while (input[*i])
	{
		printf("CARACTER: |%c|\n", input[*i]);
		printf("DELIMITADOR: |%c|\n", del);
		if (del == ' ' && (input[*i] == '\'' || input[*i] == '"'))
		{
			del = input[*i];
			(*i)++;
		}
		start = *i;
		part = extract_word(input, start, i, del);
		printf("PART: |%s|\n", part);
		if (!word)
			word = part;
		else
		{
			tmp = word;
			word = ft_strjoin(word, part);
			free(tmp);
			free(part);
		}
		//printf("%c\n", input[*i]);
		printf("WORD: %s\n", word);
		res = check_state(input, i, &del);
		printf("resultado %d\n", res);
		if (res == 1)
			break;
		if (res == 2)
			continue;
	}
	add_token(tokens, new_token(TOKEN_WORD, word, flag));
}

// Se ainda não estamos dentro de quotes e encontramos uma marcamos o delimitador
// Se terminou numa quote sai do delimitador antigo
// Se encontramos um separador fora de aspas vamos parar a leitura
// Se encontramos outra quotecontinuamos a ler
// Se tiver flag 1 de " tenho que tratar por causa da expansao das variaveis
// Tratar diretamente aqui, se nao tem par de quotes, para dar erro.
//casos para tratar | oi"ola" | -> oiola
// - | "ola"oi |-> olaoi
// - | oi'ola' |-> oiola
//falta tratar das quotes em pares.