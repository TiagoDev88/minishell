/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:54:10 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/20 01:20:58 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

// Change delimiter if we found a single or double quotes;
// If flag has_quotes is 1, it means that precendent TOKEN was a TOKEN_WORD,
// so if actual TOKEN is a TOKEN_WORD too, we
// decrement tokens count because we increment before this function call;
// And we handle too has_quotes variable in case delimiter is a space or not.
void	handle_quotes(char *line, int *delimiter, int *tokens, int *has_quotes)
{
	if (line[0])
	{
		if (line[0] == '\'' || line[0] == '"')
		{
			*delimiter = line[0];
			if (*has_quotes == 0)
				*has_quotes = 1;
			else
			{
				if (tokens)
					(*tokens)--;
			}
		}
		else
			*has_quotes = 0;
	}
}

// Sum the number of tokens in string *line. Handles single and double quotes.
int	count_tokens(char *line)
{
	int		i;
	int		tokens;
	int		has_quotes;
	int		delimiter;

	i = 0;
	tokens = 0;
	has_quotes = 0;
	while (line[i])
	{
		delimiter = ' ';
		while (line[i] == delimiter)
			i++;
		if (line[i])
			tokens++;
		handle_quotes(line + i, &delimiter, &tokens, &has_quotes); // Function to reduce lines.
		i++;
		while (line[i] && line[i] != delimiter)
			i++;
		if (line[i] && line[i] != ' ')
			i++;
	}
	return (tokens);
}

int	build_parser(char **parser, char *line, int tokens_count)
{
	int	i;
	int	j;
	int k;
	int	delimiter;
	int	has_quotes;

	i = 0;
	j = 0;
	has_quotes = 0;
	while (line[j] && i < tokens_count)
	{
		if (!parser[i])
			printf("PARSER[%i] IS CLEAN\n", i);
		else
			printf("PARSER[%i] IS NOT CLEAN\n", i);
		printf("LINE BEFORE: |%s|\n", line + j);
		delimiter = ' ';
		while (line[j] && line[j] == delimiter)
			j++;
		if (line[j] == '\'' | line[j] == '"')
		{
			delimiter = line[j];
			has_quotes = 1;
			j++;
		}
		else
		{
			if (has_quotes)
				i++;
			has_quotes = 0;
		}
		k = 0;
		while (line[j + k] && line[j + k] != delimiter)
			k++;
		if (!has_quotes)
		{
			parser[i] = ft_substr(line, j, k);
			printf("PARSER 1: %s\n", parser[i]);
			i++;
		}
		else if (has_quotes && !parser[i])
		{
			parser[i] = ft_substr(line, j, k);
			printf("PARSER 2: %s\n", parser[i]);
		}
		else if (has_quotes && parser[i])
		{
			char *temp = parser[i];
			printf("TIME TO JOIN\n");
			parser[i] = ft_strjoin(parser[i], " ");
			temp = parser[i];
			parser[i] = ft_strjoin(parser[i], ft_substr(line, j, k));
			free(temp);
			printf("PARSER 3: %s\n", parser[i]);
		}
		j += k + 1;
		if (line[j])
			printf("LINE AFTER: |%s|\n", line + j);
	}
	return (1);
}

char	**parser(char *line)
{
	int		tokens_count;
	char	**parser;

	if (!line || !line[0])
		return (NULL);
	// Count tokens
	tokens_count = count_tokens(line);
	printf("%i\n", tokens_count);
	// Allocate memory for each token + NULL
	parser = (char **)malloc(sizeof(char *) * (tokens_count + 1));
	if (!parser)
		return (NULL);
	// Initiaite all indexes to NULL. Will be easier to clean in case of error.
	ft_memset(parser, 0, sizeof(char **) * (tokens_count + 1));
	// Build split parser.
	if (!build_parser(parser, line, tokens_count))
		return (NULL);
	int i = 0;
	while (parser[i])
	{
		printf("%s\n", parser[i]);
		i++;
	}
}

int main()
{
	while (1)
	{
		char *prompt = readline("> ");
		parser(prompt);
		//int i = 0;
		
			//printf("%c\n", prompt[i]);
		add_history(prompt);
	}
}