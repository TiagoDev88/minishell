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
	char			**cmd_args;
	t_list			*args_lst;
	t_redir			*redir_in;
	t_redir			*redir_out;
	struct s_cmd	*next;
} t_cmd;


/* Main function */
int	parser(t_cmd **cmd_lst, t_token *tokens);
int	print_sintax_err(t_token *prev, t_token *curr, int status);

/* Command struct utils */
int	add_cmd(t_cmd **cmd_lst, t_token **prev, t_token **curr, int mode);
int	is_valid_redirect(t_token *curr);
int	save_cmd_args(t_list **args_lst, t_token **prev, t_token **curr);
int	save_cmd_redirects(t_cmd *cmd, t_token **prev, t_token **curr);

int	is_valid_redirect(t_token *curr);
int	is_valid_pipe(t_token **prev, t_token **curr);
int	lst_to_arr(t_list *args_lst, char ***cmd_args);

int cmd_clear(t_cmd **lst, int status);
void	redir_clean(t_redir **redir);
int	cmd_clean_split(char **split, int status);







#endif