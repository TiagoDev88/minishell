#include "../includes/token.h"


static char *extract_word(char *input, int start, int *i, int del)
{
	char	*part;

	while (input[*i])
	{
		//criar uma funcao para quando encontra $ e esta fora do single quote, para guardar e retornar
		// array e passos para o NO.
		if (del != ' ' && input[*i] == del)
			break ;
		if (del == ' ' && ft_strchr("\" '\t><|", input[*i]))
			break ;
		(*i)++;
	}
	part = ft_substr(input, start, *i - start);
	return (part);
}


static int	check_state(char *input, int *i, char *del, int *flag)
{
	if (*del != ' ' && input[*i] == *del)
	{
		(*i)++;
		if (*del == '"')
			*flag = 1;
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
		res = check_state(input, i, &del, &flag);
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
// casos para tratar | oi"ola" | -> oiola
// - | "ola"oi |-> olaoi
// - | oi'ola' |-> oiola
// falta tratar das quotes em pares.
// ter atencao a expansao das variaveis.
// echo "ola $USER'ola"'ola $USER' -> ola tfilipe-'olaola $USER
// echo "ola $USER"'Ola $USER' -> ola tfilipe-ola $USER
// echo "ola $USER" 'Ola $USER' -> ola tfilipe- ola $USER (fica com 2 tokens)
// echo "ola $USE"'R' -> ola R
// quando encontrar " e tiver $ vai ser uma variavel de ambiente, guardar logo a variavel.
// caso encontre " e um $ mesmo que seja para concatenar, e tiver o par da " colococar na mesma flag 1
// para ser variavel de ambiente, aseguir ao $ tem que ter algum caracter sem ser SPACE
// se for single quote nao e para expandir a variavel de ambiente
// depois no ECHO , fazer um strcmp com o ENVP, caso tenha depois na funcao echo
// verificar ate a envp que e passada para o no.
// tratar do $ e expandir antes de entrar no conteudo do no