#include "../../includes/minishell.h"

static void	restaure_original_stds(int *dup_ori_std)
{
	dup2(dup_ori_std[0], STDIN_FILENO);
	dup2(dup_ori_std[1], STDOUT_FILENO);
	close(dup_ori_std[0]);
	close(dup_ori_std[1]);
}

static void	get_dup_original_stds(int *dup_ori_std)
{
	int	ori_std_in;
	int	ori_std_out;

	ori_std_in = dup(STDIN_FILENO);
	ori_std_out = dup(STDOUT_FILENO);
	dup_ori_std[0] = ori_std_in;
	dup_ori_std[1] = ori_std_out;
}

static void execute(t_shell *shell, t_cmd *curr_cmd)
{
	if (!ft_strcmp(curr_cmd->cmd_args[0], "cd"))
		shell->last_status_code = ft_cd(curr_cmd, &shell->envp, shell);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "echo"))
		shell->last_status_code = ft_echo(curr_cmd);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "env"))
		shell->last_status_code = ft_env(curr_cmd, shell->envp);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "exit"))
		shell->last_status_code = ft_exit(&shell->parser.cmd_lst);
	else if (!ft_strcmp(curr_cmd->cmd_args[0], "export"))
		shell->last_status_code = ft_export(curr_cmd, &shell->envp);
	/*
	else if (ft_strcmp(curr_cmd->cmd_args[0], "pwd"))
		ft_
	else if (ft_strcmp(curr_cmd->cmd_args[0], "unset"))
		ft_echo(curr_cmd);
	*/
}

int	exec_built_in(t_shell *shell, t_cmd *curr_cmd, int single_cmd)
{
	int dup_ori_stds[2];

	if (!is_built_in(curr_cmd->cmd_args[0]))
		return (0);
	if (!shell->parser.n_pipes)
	{
		get_dup_original_stds(&dup_ori_stds[0]);
		handle_redirects(shell);
		close_last_fds(&shell->exec);
	}
	execute(shell, curr_cmd);
	if (!shell->parser.n_pipes)
		restaure_original_stds(&dup_ori_stds[0]);
	return (1);
}

