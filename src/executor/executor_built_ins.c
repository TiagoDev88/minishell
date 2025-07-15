#include "../../includes/minishell.h"

/**
 * restore_original_stds - Restores original stdin and stdout fds.
 * @dup_ori_std: Array holding duplicated original stdin and stdout fds.
 */
static void	restaure_original_stds(int *dup_ori_std)
{
	dup2(dup_ori_std[0], STDIN_FILENO);
	dup2(dup_ori_std[1], STDOUT_FILENO);
	close(dup_ori_std[0]);
	close(dup_ori_std[1]);
}

/**
 * get_dup_original_stds - Saves original stdin and stdout fds by duplicating.
 * @dup_ori_std: Array to store duplicated fds.
 */
static void	get_dup_original_stds(int *dup_ori_std)
{
	int	ori_std_in;
	int	ori_std_out;

	ori_std_in = dup(STDIN_FILENO);
	ori_std_out = dup(STDOUT_FILENO);
	dup_ori_std[0] = ori_std_in;
	dup_ori_std[1] = ori_std_out;
}

static void	execute(t_shell *shell, t_cmd *curr_cmd)
{
	if (!ft_strcmp(curr_cmd->cmd_args[0], "cd"))
		shell->last_status_code = ft_cd(curr_cmd, shell->envp, shell);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "echo"))
		shell->last_status_code = ft_echo(curr_cmd);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "env"))
		shell->last_status_code = ft_env(curr_cmd, shell->envp);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "exit"))
		shell->last_status_code = ft_exit(&shell->parser.cmd_lst, shell);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "export"))
		shell->last_status_code = ft_export(curr_cmd, &shell->envp, shell);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "pwd"))
		shell->last_status_code = ft_pwd(curr_cmd, shell->envp);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "unset"))
		shell->last_status_code = ft_unset(curr_cmd, &shell->envp);
}

/**
 * exec_built_in - Executes a built-in command, handling redirections and pipes.
 * @shell: Shell context.
 * @curr_cmd: Command to execute.
 * @single_cmd: Flag indicating if this is a single command (no pipes).
 *
 * Returns 1 if command is built-in and executed, else 0.
 */
int	exec_built_in(t_shell *shell, t_cmd *curr_cmd, int single_cmd)
{
	int		dup_ori_stds[2];
	t_envp	*under_envp;

	if (!is_built_in(curr_cmd->cmd_args[0]))
		return (0);
	if (!shell->parser.n_pipes)
	{
		update_last_cmd_env(shell, get_envp_node("_", shell->envp), curr_cmd);
		get_dup_original_stds(&dup_ori_stds[0]);
		handle_redirects(shell);
		close_last_fds(&shell->exec);
	}
	execute(shell, curr_cmd);
	if (!shell->parser.n_pipes)
		restaure_original_stds(&dup_ori_stds[0]);
	return (1);
}
