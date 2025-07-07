/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 01:02:36 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/07 00:17:46 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_cmd(t_token **curr)
{
	t_token	*tmp;

	tmp = *curr;
	while (*curr && (*curr)->type == TOKEN_WORD)
		*curr = (*curr)->next;
	if (tmp != *curr)
		return (1);
	return (0);
}

void	validate_cmd(char *cmd_path, t_exec *exec)
{
	struct stat sb;

	if (stat(cmd_path, &sb) != 0) // Verifica se o ficheiro existe.
		print_cmd_err_and_exit(cmd_path, 1, 127, exec);
	if (S_ISDIR(sb.st_mode)) // Verifica se é um diretorio
		print_cmd_err_and_exit(cmd_path, 0, 126, exec);
	if (access(cmd_path, X_OK) != 0) // sem permissoes
		print_cmd_err_and_exit(cmd_path, 1, 126, exec);
}

int	validate_and_open_files(t_token **curr_token, t_exec *exec)
{
	int	exit_status;

	exit_status = 0;
	while (*curr_token && ((*curr_token)->type >= TOKEN_REDIR_OUT && (*curr_token)->type <= TOKEN_HEREDOC))
	{
		exit_status = add_file(&exec->files_container, (*curr_token)->next->value, (*curr_token)->type);
		if (exit_status == -1)
		{
			print_error_msg(NULL, strerror(errno), 1);
			exit_clean(exec, errno);
		}
		if (exit_status > 0)
		{
			EXIT_STATUS = 1;
			print_file_err_and_return((*curr_token)->next->value, strerror(exit_status), 0);
			while (*curr_token && ((*curr_token)->type >= TOKEN_REDIR_OUT && (*curr_token)->type <= TOKEN_HEREDOC))
				*curr_token = (*curr_token)->next->next;
			return(0);
		}
		*curr_token = (*curr_token)->next->next;
	}
	return (1);
}
