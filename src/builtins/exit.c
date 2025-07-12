

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

static int only_num(char *s)
{
	int i;

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

static long long ft_atoll(char *str)
{
	long long result;
	int sign;

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

int	ft_exit(t_cmd **cmd, t_shell *sh)
{
	long long code;
	char *arg;

	ft_putendl_fd("exit", 1);
	if (!(*cmd)->cmd_args[1] || ft_strcmp((*cmd)->cmd_args[1], "--") == 0)
		exit_clean(sh, EXIT_SUCCESS);
	arg = (*cmd)->cmd_args[1];
	if (!only_num(arg) || ft_strncmp(arg, "9223372036854775808", 19) >= 0)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_clean(sh, 2);
	}
	if ((*cmd)->cmd_args[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		sh->last_status_code = 1;
		return (1);
	}
	code = ft_atoll(arg);
	exit_clean(sh, (unsigned char)code);
	return (0);
}
