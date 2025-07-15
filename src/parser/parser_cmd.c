/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 01:17:32 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/15 23:10:54 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * cmd_create_node - Allocates and initializes a new command node.
 *
 * Allocates memory for a new t_cmd structure, initializing all its fields to NULL.
 *
 * Return: Pointer to the newly created node, or NULL if allocation fails.
 */
t_cmd	*cmd_create_node(void)
{
	t_cmd	*t_cmd_new;

	t_cmd_new = malloc(sizeof(t_cmd));
	if (!t_cmd_new)
		return (NULL);
	t_cmd_new->next = NULL;
	t_cmd_new->redir_in = NULL;
	t_cmd_new->redir_out = NULL;
	t_cmd_new->args_lst = NULL;
	t_cmd_new->cmd_args = NULL;
	t_cmd_new->cmd_path = NULL;
	return (t_cmd_new);
}

/**
 * cmd_add_back - Appends a command node to the end of the command list.
 * @lst: Pointer to the head of the command list.
 * @new: The new node to append.
 *
 * If the list is empty, the new node becomes the head.
 * Otherwise, the function traverses the list and adds the new node to the end.
 */
void	cmd_add_back(t_cmd	**lst, t_cmd *new)
{
	t_cmd	*curr;

	if (!new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		curr = *lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

/**
 * add_mode_two - Creates and adds a new command (mode 2) with args and redirects.
 * @cmd_lst: Pointer to the list of commands.
 * @prev: Pointer to the previous token pointer.
 * @curr: Pointer to the current token pointer.
 *
 * Used when a WORD token is found and expected to contain both arguments and redirections.
 * It creates a command node, saves arguments and redirections, and converts the args list to an array.
 *
 * Return: 1 on success, 0 on error.
 */
int	add_mode_two(t_cmd **cmd_lst, t_token **prev, t_token **curr)
{
	t_cmd	*new;

	new = cmd_create_node();
	if (!new)
		return (0);
	cmd_add_back(cmd_lst, new);
	if (!save_cmd_args(&new->args_lst, prev, curr))
		return (0);
	if (!save_cmd_redirects(new, prev, curr))
		return (0);
	if (!save_cmd_args(&new->args_lst, prev, curr))
		return (0);
	return (lst_to_arr(new->args_lst, &new->cmd_args));
}


/**
 * add_mode_one - Creates and adds a new command (mode 1) starting with a redirection.
 * @cmd_lst: Pointer to the list of commands.
 * @prev: Pointer to the previous token pointer.
 * @curr: Pointer to the current token pointer.
 *
 * Used when a command starts with a redirection (e.g., "> out.txt ls").
 * Saves redirections and checks if a valid command follows.
 * If not, cleans up the partially built command.
 *
 * Return: 1 on success or when no command is added, 0 on error.
 *
 */
int	add_mode_one(t_cmd **cmd_lst, t_token **prev, t_token **curr)
{
	t_cmd	*new;

	new = cmd_create_node();
	if (!new)
		return (0);
	if (!save_cmd_redirects(new, prev, curr))
		return (0);
	if (*curr && (*curr)->type == TOKEN_WORD)
	{
		cmd_add_back(cmd_lst, new);
		if (!save_cmd_args(&new->args_lst, prev, curr))
			return (0);
		if (!save_cmd_redirects(new, prev, curr))
			return (0);
		if (!save_cmd_args(&new->args_lst, prev, curr))
			return (0);
		return (lst_to_arr(new->args_lst, &new->cmd_args));
	}
	redir_clean(&new->redir_in);
	redir_clean(&new->redir_out);
	free(new);
	return (1);
}

/**
 * add_cmd - Dispatcher for adding a command node depending on parsing mode.
 * @cmd_lst: Pointer to the list of commands.
 * @prev: Pointer to the previous token pointer.
 * @curr: Pointer to the current token pointer.
 * @mode: Determines how to parse the tokens (1 = redir first, 2 = word first).
 *
 * Calls add_mode_one or add_mode_two depending on the mode value.
 *
 * Return: 1 on success, 0 on failure.
 */
int	add_cmd(t_cmd **cmd_lst, t_token **prev, t_token **curr, int mode)
{
	if (mode == 1)
	{
		if (!add_mode_one(cmd_lst, prev, curr))
			return (0);
	}
	else
	{
		if (!add_mode_two(cmd_lst, prev, curr))
			return (0);
	}
	return (1);
}
