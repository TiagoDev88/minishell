/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:37:36 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/06/30 15:37:36 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO: depois tenho que ver como vou tratar do exit status
// vai ser com a variavel global, o EXIT CODE
// substituir $? pelo exit status
/**
 * @brief Extracts the value of an environment variable from the input string.
 *
 * This function parses the variable name after the '$' character.
 * 
 * If the variable is `$?`, it returns the exit status as a string.
 * 
 * Otherwise, it fetches the value from the environment using `getenv`.
 *
 * @param bd Pointer to the token builder containing the input and position.
 * @return A dynamically allocated string with the variable's value, or an 
 * empty string if not found.
 */
static char	*extract_variable(t_token_builder *bd)
{
	char	var[256];
	int		j;
	char	*value;

	j = 0;
	bd->pos++;
	var[0] = '\0';
	if (bd->input[bd->pos] == '?')
	{
		bd->pos++;
		return (ft_itoa(69));
	}
	while (bd->input[bd->pos] && (ft_isalpha(bd->input[bd->pos])
			|| bd->input[bd->pos] == '_'))
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

/**
 * @brief Checks if the variable after the '$' symbol should be ignored.
 *
 * This function handles cases like:
 * 
 * - `$` at the end of the input.
 * 
 * - `$` followed by a digit (positional parameter, which is ignored in 
 * this implementation).
 *
 * @param bd Pointer to the token builder.
 * @param start Pointer to the start position index to update if needed.
 * @return int
 * 
 * - 1: Variable should be ignored (e.g., `$5` or `$` at end).
 * 
 * - 0: Continue processing.
 */
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

/**
 * @brief Appends a text segment from the input to the current part of the word.
 *
 * This function takes the substring from `*start` to the current position and
 * 
 * appends it to `*part`, reallocating memory as needed.
 *
 * @param bd Pointer to the token builder.
 * @param part Pointer to the current partial word being built.
 * @param start Pointer to the start index of the substring to append.
 */
static void	append_text(t_token_builder **bd, char **part, int *start)
{
	char	*tmp;
	char	*env_val;

	if (!*part)
		*part = ft_strdup("");
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

/**
 * @brief Handles the appending of text and/or environment variable
 *  values to the current word part.
 *
 * This function appends plain text if `flag == 0`, or resolves and
 *  appends a variable value if `flag == 1`. 
 * 
 * It handles memory allocation and updating of the input position.
 *
 * @param bd Pointer to the token builder.
 * @param part Pointer to the current partial word being built.
 * @param start Pointer to the start index for appending.
 * @param flag Determines the operation:
 *  - 0: Only append text from `*start` to `pos`.
 *  - 1: Also resolve and append the variable value.
 * @return int
 * - 1: Success.
 * - 0: Memory allocation failure.
 */
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

/**
 * @brief Handles different cases when encountering a '$' character.
 *
 * This function decides how to process a dollar sign in the input:
 * 
 * - Ignores invalid or standalone `$`.
 * 
 * - Ignores positional parameters (e.g., `$1`).
 * 
 * - Resolves and appends the environment variable value if not 
 * inside single quotes.
 *
 * @param bd Pointer to the token builder.
 * @param part Pointer to the current partial word being built.
 * @param start Pointer to the start index for the current word part.
 * @return int
 * 
 * - 0: No special handling required, continue processing.
 * 
 * - 1: Variable processed or skipped, word should continue or break.
 * 
 * - 2: Standalone or invalid `$` was skipped.
 */
int	check_dollar_cases(t_token_builder **bd, char **part, int *start)
{
	char	next;

	if ((*bd)->input[(*bd)->pos] == '$')
	{
		next = (*bd)->input[(*bd)->pos + 1];
		if (next == '\0' || next == ' ' || ft_strchr("\"\'\t><|", next))
		{
			(*bd)->pos++;
			return (STATE_CONTINUE);
		}
		if (is_ignored_variable(bd, start))
			return (STATE_BREAK);
		if ((*bd)->del != '\'')
		{
			append_dollar(bd, part, start, 1);
			return (STATE_BREAK);
		}
	}
	return (STATE_CONTINUE);
}
