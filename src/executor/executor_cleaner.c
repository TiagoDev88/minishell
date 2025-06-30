/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 23:03:44 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/29 23:47:06 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_clean(t_exec *exec, char *error, int exit_status)
{
	if (exec->files_container.lst)
		clean_files(exec->files_container.lst);
	ft_putstr_fd(2, "bash: ");
	ft_putstr_fd(2, error);
	exit(exit_status);
}