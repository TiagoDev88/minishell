/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:31:28 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/15 23:19:32 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Contains all functions to clean all memory allocated in 
	main struct T_CMD and sub structures
*/

#include "../../includes/minishell.h"

/**
 * cmd_clean_split - Frees a NULL-terminated array of strings.
 * @split: The array to free.
 * @status: Status code to return after cleanup.
 *
 * Iterates over the string array, freeing each string, then frees the array itself.
 *
 * Return: The provided status value.
 */
int	cmd_clean_split(char **split, int status)
{
	int	i;

	if (!split)
		return (status);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (status);
}

/**
 * redir_clean - Frees a list of redirection structures.
 * @redir: Pointer to the head of the t_redir list.
 *
 * Frees each node in the redirection list, including the filename,
 * and sets the list pointer to NULL.
 */
void	redir_clean(t_redir **redir)
{
	t_redir	*curr;
	t_redir	*tmp;

	if (!(*redir) || !redir)
		return ;
	curr = *redir;
	while (curr)
	{
		tmp = curr->next;
		free(curr->filename);
		free(curr);
		curr = tmp;
	}
	*redir = NULL;
}

/**
 * clean_cmds - Cleans the full command list and associated memory.
 * @parser: Pointer to the parser structure (used to reset n_pipes).
 * @lst: Pointer to the head of the t_cmd command list.
 * @status: Status code to return after cleanup.
 *
 * Frees all resources allocated in each t_cmd node including:
 * - cmd_path
 * - cmd_args array
 * - redirection lists
 * - argument linked list
 * 
 * Also resets the command list pointer and parser's pipe counter.
 *
 * Return: The provided status value.
 */
int	clean_cmds(t_parser *parser, t_cmd **lst, int status)
{
	t_cmd	*curr;
	t_cmd	*tmp;

	if (!lst || !*lst)
		return (status);
	curr = *lst;
	while (curr)
	{
		if (curr->cmd_path)
			free(curr->cmd_path);
		cmd_clean_split(curr->cmd_args, 0);
		redir_clean(&curr->redir_in);
		redir_clean(&curr->redir_out);
		ft_lstclear(&curr->args_lst, &free);
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*lst = NULL;
	parser->n_pipes = 0;
	return (status);
}
