#ifndef TOKEN_H
# define TOKEN_H


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
	struct s_token *next;
}	t_token;

typedef struct s_token_builder
{
    char    *input;
    char    **envp;
    int     pos;
    char    del;
}   t_token_builder;



t_token	*tokenize(char *, char **);
void	free_tokens(t_token *);
void handle_word(t_token **, t_token_builder *);
void add_token(t_token **, t_token *);
t_token *new_token(t_token_type , const char *);
int	append_dollar(t_token_builder **bd, char **part, int *start, int flag);
int	check_dollar_cases(t_token_builder **bd, char **part, int *start);

#endif