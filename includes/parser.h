#ifndef PARSER_H
# define PARSER_H


# define ERR_SINTAX_NEAR_PIPE "bash: syntax error near unexpected token `|'\n"
# define ERR_SINTAX_NEAR_APPEND  "bash: syntax error near unexpected token `>>'\n"
# define ERR_SINTAX_NEAR_HEREDOC  "bash: syntax error near unexpected token `<<'\n"
# define ERR_SINTAX_NEAR_REDIR_IN  "bash: syntax error near unexpected token `<'\n"
# define ERR_SINTAX_NEAR_REDIR_OUT "bash: syntax error near unexpected token `>'\n"
# define ERR_SINTAX_NO_TOKEN_AFTER "bash: syntax error near unexpected token `newline'\n"

typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd;
	t_redir			*redir_in;
	t_redir			*redir_out;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_parser_counts
{
	int	cmds;
	int	pipes;
	int redir_out;
	int	redir_in;
	int	appends;
	int heredoc;
}	t_parser_counts;

typedef struct s_file
{
	char			*filename;
	int				fd;
	struct s_file	*next;
}	t_file;


/* Main function */
int	parser(t_cmd **cmd_lst, t_token *tokens);
int	print_sintax_err(t_token *curr, int status);

/* Command struct utils */
int	add_cmd(t_cmd **cmd_lst, t_token **prev, t_token **curr);



#endif