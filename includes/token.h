#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

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
	int				double_quote;
	char			*env;
	struct s_token *next;
}	t_token;


t_token	*tokenize(char *input);
void	free_tokens(t_token *tokens);
void handle_word(t_token **tokens, char *input, int *i, char del);
void add_token(t_token **tokens, t_token *new);
t_token *new_token(t_token_type type, const char *value, int flag);

#endif