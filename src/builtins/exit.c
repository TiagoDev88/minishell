#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

static int	only_num(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atoll(char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

static int	compare_overflow(char *num, char *max)
{
	int	i;

	i = 0;
	while (num[i] && max[i])
	{
		if (num[i] > max[i])
			return (1);
		else if (num[i] < max[i])
			return (0);
		i++;
	}
	return (0);
}

static int	is_overflow(char *arg)
{
	int		sign;
	char	*num;
	int		len;

	sign = 1;
	if (*arg == '+' || *arg == '-')
	{
		if (*arg == '-')
			sign = -1;
		arg++;
	}
	num = arg;
	len = 0;
	while (ft_isdigit(num[len]))
		len++;
	if (num[len] != '\0')
		return (1);
	if (len < 19)
		return (0);
	if (len > 19)
		return (1);
	if (sign == 1)
		return (compare_overflow(num, "9223372036854775807"));
	else
		return (compare_overflow(num, "9223372036854775808"));
}

/**
 * @brief Implements the builtin `exit` command with argument validation
 *  and proper exit codes.
 * 
 * Prints "exit" to stdout. If no argument or "--" is given, 
 * exits with status 0.
 * If the first argument is not a valid numeric string or is out of range,
 * prints an error and exits with status 2.
 * If more than one argument is given, prints an error message,
 * sets the shell's last status to 1 and does not exit.
 * Otherwise, converts the argument to a number and exits with that status.
 * 
 * @param cmd Double pointer to the current command structure,
 *  which contains the arguments.
 * @param sh Pointer to the shell structure, used for cleanup and exit.
 * 
 * @return Returns 1 if too many arguments are provided (does not exit).
 *         Does not return on successful exit or fatal error exit.
 */
int	ft_exit(t_cmd **cmd, t_shell *sh)
{
	long long	code;
	char		*arg;

	if (!sh->exec.procc_lst)
		ft_putendl_fd("exit", 1);
	if (!(*cmd)->cmd_args[1] || ft_strcmp((*cmd)->cmd_args[1], "--") == 0)
		exit_clean(sh, EXIT_SUCCESS, 1);
	arg = (*cmd)->cmd_args[1];
	if (!only_num(arg) || is_overflow(arg))
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_clean(sh, 2, 1);
	}
	if ((*cmd)->cmd_args[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		sh->last_status_code = 1;
		return (1);
	}
	code = ft_atoll(arg);
	exit_clean(sh, (unsigned char)code, 1);
	return (0);
}
