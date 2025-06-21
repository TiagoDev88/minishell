#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_cmd
{
	char **cmd;
	// Possible fields:
		// Redirect stdin;
		// Redirect stdout;
	// Lista linkada para ja
	struct s_cmd *next;
} t_cmd;


int build_cmds(t_cmd **lst, t_token *head);

#endif