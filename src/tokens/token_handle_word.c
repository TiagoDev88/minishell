/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:45:21 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/15 16:36:19 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

/**
 * @brief Check current parsing state related to quotes or delimiters.
 *
 * This function checks if the current character opens or closes a quote,
 * or if it hits a word-breaking delimiter (like space, tab, pipe, etc.).
 * It also returns an error if there's an unclosed quote at the end.
 *
 * @param bd Pointer to the token builder structure.
 * @param start Pointer to the starting index of the word.
 * @return int:
 *   - STATE_ERROR (-1): Unclosed quote or syntax error.
 *   - STATE_CONTINUE (0): Keep reading.
 *   - STATE_BREAK (1): Word is finished.
 *   - STATE_QUOTE_CHANGE (2): Opened or closed a quote.
 */
static int	check_state(t_token_builder *bd, int *start)
{
	if (bd->del != ' ' && bd->input[bd->pos] == bd->del)
	{
		bd->pos++;
		bd->del = ' ';
		return (STATE_QUOTE_CHANGE);
	}
	if (bd->del == ' ' && ft_strchr("'\" \t><|$", bd->input[bd->pos]))
	{
		if ((bd->input[bd->pos] == '\'' || bd->input[bd->pos] == '"'))
		{
			bd->del = bd->input[bd->pos];
			*start = bd->pos;
			bd->pos++;
			if (bd->input[bd->pos] == '\0' && bd->del != ' ')
				return (STATE_ERROR);
			return (STATE_QUOTE_CHANGE);
		}
		return (STATE_BREAK);
	}
	if (bd->input[bd->pos] == '\0' && bd->del != ' ')
		return (STATE_ERROR);
	return (STATE_CONTINUE);
}

/**
 * @brief Append a part to the current word, handling memory allocation.
 *
 * If the word is NULL, assigns the part directly. Otherwise,
 * it joins the existing word with the new part using ft_strjoin,
 * and frees the old memory.
 *
 * @param word Pointer to the current word string.
 * @param part String to append to the word.
 * @return int: 1 on success, 0 on memory allocation failure.
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
 * @brief Extract a word from the input based on current position and state.
 *
 * Reads characters from the input string while respecting the current quote
 * and delimiter state. Handles dollar expansion and ends when a valid
 * delimiter or special character is found.
 *
 * @param bd Pointer to the token builder.
 * @param start Pointer to the starting index of the word.
 * @return char*: The extracted word, or NULL on failure.
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
		if (check == STATE_NULL)
			break ;
		if ((*bd)->del != ' ' && (*bd)->input[(*bd)->pos] == (*bd)->del)
			break ;
		if ((*bd)->del == ' ' && ft_strchr("\"$ '\t><|",
				(*bd)->input[(*bd)->pos]))
			break ;
		(*bd)->pos++;
	}
	if ((*bd)->pos > *start)
		return (append_dollar(bd, &part, start, 0), part);
	if ((*bd)->pos == *start && (*bd)->del == ' ' && (*bd)->startbefdol != '$')
		return (ft_strdup(""));
	return (NULL);
}

/**
 * @brief Extract a word and append it to the current token being built.
 *
 * Uses `extract_word()` and `word_append()` to assemble a full word
 * part-by-part. Handles syntax errors and quote state changes.
 *
 * @param tokens Token list to which the new token will be added.
 * @param bd Pointer to the token builder structure.
 * @param word Pointer to the current word being assembled.
 * @param start Pointer to the starting index of the word.
 * @return int: One of the STATE_ constants indicating the current parsing state.
 */
static int	extract_and_append(t_token **tokens, t_token_builder *bd,
					char **word, int *start)
{
	char	*part;
	int		res;

	part = extract_word(&bd, start);
	if (!part)
		return (STATE_ERROR);
	if (!word_append(word, part))
		return (free(word), STATE_ERROR);
	res = check_state(bd, start);
	if (res == STATE_ERROR)
	{
		clean_words(tokens, *word, STATE_ERROR);
		return (STATE_ERROR);
	}
	return (res);
}

/**
 * @brief Extract and handle a word token from the input.
 *
 * Reads the input string, identifies words and handles quote
 * logic and dollar expansion. Once the word is complete, adds
 * it as a new token to the token list.
 *
 * @param tokens Pointer to the list of tokens.
 * @param bd Pointer to the token builder.
 */
void	handle_word(t_token **tokens, t_token_builder *bd)
{
	char	*word;
	int		res;
	int		start;

	word = ft_strdup("");
	res = check_state(bd, &start);
	if (res == STATE_ERROR)
		return (clean_words(tokens, word, STATE_ERROR));
	while (bd->input[bd->pos])
	{
		res = check_state(bd, &start);
		if (res == STATE_ERROR)
			return (clean_words(tokens, word, STATE_ERROR));
		if (res == STATE_QUOTE_CHANGE)
			continue ;
		start = bd->pos;
		res = extract_and_append(tokens, bd, &word, &start);
		if (res == STATE_ERROR)
			return ;
		if (res == STATE_BREAK)
			break ;
		if (res == STATE_CONTINUE)
			continue ;
	}
	add_token(tokens, new_token(TOKEN_WORD, word));
}
