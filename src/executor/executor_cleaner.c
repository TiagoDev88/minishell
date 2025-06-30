/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 23:03:44 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/30 10:24:13 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_clean(t_exec *exec, char *error, int exit_status)
{
	if (exec->files_container.lst)
		clean_files(&exec->files_container.lst);
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(error, 2);
	exit(exit_status);
}