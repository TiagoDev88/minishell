/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:43:29 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/14 10:09:42 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef TOKEN_H
# define TOKEN_H

struct					s_envp;
typedef struct s_envp	t_envp;
typedef struct s_shell	t_shell;

typedef enum e_check_state
{
	STATE_ERROR = -1,
	STATE_CONTINUE = 0,
	STATE_BREAK = 1,
	STATE_QUOTE_CHANGE = 2,
	STATE_NULL = 3
}	t_check_state;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_token_builder
{
	char	*input;
	t_envp	*envp;
	int		pos;
	char	del;
	int		startbefdol;
	int		*last_status_code;
}	t_token_builder;

t_token	*tokenize(char *input, t_envp **envp, t_shell *shell);
void	free_tokens(t_token **tk);
void	handle_word(t_token **tokens, t_token_builder *bd);
void	add_token(t_token **tk, t_token *new);
t_token	*new_token(t_token_type type, char *value);
int		append_dollar(t_token_builder **bd, char **part, int *start, int flag);
int		check_dollar_cases(t_token_builder **bd, char **part, int *start);
void	clean_words(t_token **tk, char *word, int res);

#endif