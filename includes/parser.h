/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:01:29 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/19 15:16:19 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# define ERR_NEAR_PIPE "bash: syntax error near unexpected token `|'"
# define ERR_NEAR_APPEND  "bash: syntax error near unexpected token `>>'"
# define ERR_NEAR_HEREDOC  "bash: syntax error near unexpected token `<<'"
# define ERR_NEAR_REDIR_IN  "bash: syntax error near unexpected token `<'"
# define ERR_NEAR_REDIR_OUT "bash: syntax error near unexpected token `>'"
# define ERR_TOKEN_AFTER "bash: syntax error near unexpected token `newline'"
# define ERR_D ".: filename argument required\n.: usage: . filename [arguments]"

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
	char			*cmd_path;
	t_redir			*redir_in;
	t_redir			*redir_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_parser
{
	t_cmd	*cmd_lst;
	int		n_pipes;
}	t_parser;

/* Main function */
int		parser(t_parser *parser_s, t_token *tokens, t_shell *shell);
/* Command struct utils */
int		add_cmd(t_cmd **cmd_lst, t_token **prev, t_token **curr, int mode);
int		is_valid_redirect(t_token *curr);
int		save_cmd_args(t_list **args_lst, t_token **prev, t_token **curr);
int		save_cmd_redirects(t_cmd *cmd, t_token **prev, t_token **curr);
/* Validator */
int		is_valid_redirect(t_token *curr);
int		is_valid_pipe(t_token **prev, t_token **curr, int *n_pipes);
int		lst_to_arr(t_list *args_lst, char ***cmd_args);
/* Cleaner */
int		clean_cmds(t_parser *parser, t_cmd **lst, int status);
void	redir_clean(t_redir **redir);
int		cmd_clean_split(char **split, int status);

#endif