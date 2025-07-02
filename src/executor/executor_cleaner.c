/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 23:03:44 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/02 02:01:31 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_clean(t_exec *exec, char *error, int exit_status)
{
	if (exec->files_container.lst)
		clean_files(&exec->files_container.lst);
	return(exit_status);
}

void	exit_clean(t_exec *exec, int exit_status)
{
	if (exec->files_container.lst)
		clean_files(&exec->files_container.lst);
	EXIT_STATUS = exit_status;
	exit(exit_status);
}

int clean_mem(void *p1, void *p2, void *p3, int exit_status)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p3);
	return (exit_status);
}