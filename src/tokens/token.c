/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:49:57 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/11 15:16:51 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Determines the token type from the given string.
 *
 * Checks if the input string matches known shell operators
 * 
 * like append (>>), heredoc (<<), redirections (> or <), or pipe (|).
 * 
 * If none match, it returns TOKEN_WORD.
 *
 * @param s Pointer to the input string.
 * @return The token type corresponding to the input string.
 */
static t_token_type	get_token_type(const char *s)
{
	if (!ft_strncmp(s, ">>", 2))
		return (TOKEN_APPEND);
	if (!ft_strncmp(s, "<<", 2))
		return (TOKEN_HEREDOC);
	if (*s == '>')
		return (TOKEN_REDIR_OUT);
	if (*s == '<')
		return (TOKEN_REDIR_IN);
	if (*s == '|')
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}

/**
 * @brief Helper function to tokenize the input string.
 *
 * Parses the input starting at the current position in the token builder.
 * 
 * Detects multi-character tokens (>>, <<), single-character tokens (> < |),
 * 
 * or words possibly enclosed in quotes. It adds the extracted
 *  tokens to the list.
 *
 * @param tk Pointer to the head of the token list.
 * @param bd Pointer to the token builder structure holding input state.
 * @param substr Temporary string used to hold extracted substrings.
 */
static void	help_tokenize(t_token **tk, t_token_builder *bd, char *substr)
{
	if (!ft_strncmp(&bd->input[bd->pos], ">>", 2)
		|| !ft_strncmp(&bd->input[bd->pos], "<<", 2))
	{
		substr = ft_substr(bd->input, bd->pos, 2);
		add_token(tk, new_token(get_token_type(&bd->input[bd->pos]), substr));
		bd->pos += 2;
	}
	else if (ft_strchr("> < |", bd->input[bd->pos]))
	{
		substr = ft_substr(bd->input, bd->pos, 1);
		add_token(tk, new_token(get_token_type(&bd->input[bd->pos]), substr));
		bd->pos++;
	}
	else
	{
		if (bd->input[bd->pos] == '\"' || bd->input[bd->pos] == '\'')
		{
			bd->del = bd->input[bd->pos];
			bd->pos++;
		}
		handle_word(tk, bd);
	}
}

/**
 * @brief Tokenizes the entire input string into a linked list of tokens.
 *
 * Skips whitespace, iterates through the input, and calls the helper tokenizer
 * 
 * to parse tokens until the end of the input string is reached.
 *
 * @param input The command line input string to tokenize.
 * @param envp The environment variables array (unused in the
 *  shown code but passed).
 * @return Pointer to the head of the generated token linked list.
 */
t_token	*tokenize(char *input, t_envp **envp, t_shell *shell)
{
	t_token_builder	bd;
	t_token			*tk;
	char			*substr;

	bd.input = input;
	bd.envp = envp;
	bd.pos = 0;
	bd.last_status_code = &shell->last_status_code;
	tk = NULL;
	substr = NULL;
	while (bd.input[bd.pos])
	{
		bd.del = ' ';
		while (bd.input[bd.pos] == ' ' || bd.input[bd.pos] == '\t')
			bd.pos++;
		if (!bd.input[bd.pos])
			break ;
		help_tokenize(&tk, &bd, substr);
	}
	return (tk);
}
