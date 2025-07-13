/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:45:21 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/12 23:49:16 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static void	clean_words(t_token **tk, char *word, int res)
{
	if (res == -1)
		printf("minishell: syntax error: unclosed quote\n");
	if (word)
		free(word);
	if (tk && *tk)
		free_tokens(tk);
}

//TODO tratar do erro das quotes nao terem pares
// talvez escrever o erro das quotes para o strerror

/**
 * @brief Checks the current parsing state regarding quotes and special
 *  characters.
 *
 * This function analyzes the character at the current `bd->pos` position
 *  to determine whether to:
 * 
 * - Close an open quote (e.g., closing " or ')
 * - Open a new quote (if no quote is currently active and the character
 *  is ' or ")
 * 
 * - End the reading of a word when encountering a delimiter (space, tab,
 *  pipe, etc.)
 * 
 * - Report a syntax error if there is an unclosed quote at the end of the
 *  input.
 *
 * @param bd Pointer to the token builder structure (`t_token_builder`),
 * 
 *           which contains the input, current position, and active delimiter.
 * @return int
 * - -1: Syntax error (e.g., unclosed quote).
 * -  0: Normal state, continue reading.
 * 
 * -  1: Word is complete (delimiter found outside of quotes).
 * -  2: State change (opened or closed a quote).
 */
static int	check_state(t_token_builder *bd, int *start)
{
	if (bd->del != ' ' && bd->input[bd->pos] == bd->del)
	{
		bd->pos++;
		bd->del = ' ';
		return (STATE_QUOTE_CHANGE);
	}
	if (bd->del == ' ' && ft_strchr("'\" \t><|", bd->input[bd->pos]))
	{
		if ((bd->input[bd->pos] == '\'' || bd->input[bd->pos] == '"')) // se estiver errado voltar a colocar a verificacao bd->input[bd->pos + 1] != '\0' && 
		{
			bd->del = bd->input[bd->pos];
			*start = bd->pos;
			bd->pos++;
			return (STATE_QUOTE_CHANGE);
		}
		return (STATE_BREAK);
	}
	if (bd->input[bd->pos] == '\0' && bd->del != ' ')
		return (STATE_ERROR);
	return (STATE_CONTINUE);
}

/**
 * @brief Appends a part to the word, dynamically allocating memory as needed.
 * 
 * This function checks if the word is currently NULL, in which case it 
 * assigns the part directly
 * or appends the part to the existing word.
 * @param word Pointer to the word string that will be modified.
 * @param part The part to be appended to the word.
 * @return 1 on success, 0 on failure (memory allocation error).
 */
static int	word_append(char **word, char *part)
{
	char	*tmp;

	tmp = NULL;
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

/**
 * @brief Extracts a word from the input string based on the current 
 * position and delimiter.
 * 
 * This function reads characters from the input string until it encounters
 *  a delimiter
 * 
 * or the end of the string. It constructs a word by appending characters to it,
 * 
 * taking care of special cases like quotes and dollar signs.
 * @param bd Pointer to the token builder containing the input string and
 *  current position.
 * @param start The starting position of the word in the input string.
 * @return A dynamically allocated string containing the extracted word, or
 *  NULL on failure.
 */
static char	*extract_word(t_token_builder **bd, int *start)
{
	char	*part;
	int		check;

	part = ft_strdup("");
	if (!part)
		return (NULL);
	while ((*bd)->input[(*bd)->pos])
	{
		check = check_dollar_cases(bd, &part, start);
		if (check == STATE_BREAK)
			return (part);
		if (check == 3)
			break ;
		if ((*bd)->del != ' ' && (*bd)->input[(*bd)->pos] == (*bd)->del)
			break ;
		if ((*bd)->del == ' ' && ft_strchr("\"$ '\t><|",
				(*bd)->input[(*bd)->pos]))
			break;
		if ((*bd)->input[(*bd)->pos])
			(*bd)->pos++;
	}
	if ((*bd)->pos > *start)
	{
		append_dollar(bd, &part, start, 0);
		return (part);
	}
	if ((*bd)->pos == *start && (*bd)->del == ' ' && (*bd)->input[0] != '$')
		return (ft_strdup(""));
	return (NULL);
}

/**
 * @brief Handles the extraction of a word from the input string and adds it
 *  as a token.
 * 
 * This function reads characters from the input string until it encounters a 
 * delimiter
 * 
 * or the end of the string. It constructs a word by appending characters to it,
 * 
 * taking care of special cases like quotes and dollar signs.
 * 
 * check first character after quote, in variable RES = check_state.
 * 
 * Because its ERROR, if only one quote.
 * @param tokens Pointer to the list of tokens where the new token will be added.
 * @param bd Pointer to the token builder containing the input string and current
 *  position.
 * @return void
 */
 void	handle_word(t_token **tokens, t_token_builder *bd)
 {
     char	*word;
     char	*part;
     int		start;
     int		res;

     word = ft_strdup("");
     while (bd->input[bd->pos])
     {
        res = check_state(bd, &start);
        if (res == STATE_ERROR)
             return (clean_words(tokens, word, STATE_ERROR));
         if (res == STATE_QUOTE_CHANGE)
             continue;           // só mudou aspas; não corta o token nem aborta
        start = bd->pos;
        part = extract_word(&bd, &start);
        if (!part)
            return ;
        if (!word_append(&word, part))
            return (free(word));

        res = check_state(bd, &start);
        if (res == STATE_ERROR)
            return (clean_words(tokens, word, STATE_ERROR));
        if (res == STATE_BREAK)
            break ;
        if (res == STATE_CONTINUE)
            continue;
     }
     add_token(tokens, new_token(TOKEN_WORD, word));
 }

 
 