//TODO no exit, ele pega em qualquer numero (o valor)
// faz modulo talvez de 256, e assume o retorno
// 
/*
tfilipe-@c1r16s7:~$ bash
tfilipe-@c1r16s7:~$ exit 257
exit
tfilipe-@c1r16s7:~$ echo $?
1
tfilipe-@c1r16s7:~$ bash
tfilipe-@c1r16s7:~$ exit 258
exit
tfilipe-@c1r16s7:~$ echo $?
2
tfilipe-@c1r16s7:~$ bash
tfilipe-@c1r16s7:~$ exit 300
exit
tfilipe-@c1r16s7:~$ echo $?
44
tfilipe-@c1r16s7:~$ bash
tfilipe-@c1r16s7:~$ exit 256
exit
tfilipe-@c1r16s7:~$ echo $?
0
tfilipe-@c1r16s7:~$ bash
tfilipe-@c1r16s7:~$ exit 255
exit
tfilipe-@c1r16s7:~$ echo $?
255
*/

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
static  int only_num(char *s)
{
    int i;

    i = 0;
    if (2 == ft_strlen(s))
    {
        while (s[i] == '+' || s[i] == '-')
            i++;
    }
    // if (!s || !s[0])
    //     return (0);
    // if (s[0] == '+' || s[1] == '+' || s[0] == '-' || s[1] == '-')
    //     i++;
    if (s[2] == '+' || s[2] == '-')
        return (0);
    if (s[2] == '\0' && s[1] == '-')
        return (1);
    while (s[i])
    {
        //printf("c |%c|\n", s[i]);
        if (!ft_isdigit(s[i]))
            return (0);
        i++;
    }
    return (i);
}

int	ft_exit(t_cmd **cmd, t_shell *sh)
{
    int i;
    long long code;

    // printf("exit\n");
    ft_putendl_fd("exit", 1);
    if (!cmd || !*cmd || !(*cmd)->cmd_args[1])
        exit_clean(sh, EXIT_SUCCESS);
    if (only_num((*cmd)->cmd_args[1]) == 0)
    {
        ft_putstr_fd("bash: exit: ", 2);
        ft_putstr_fd((*cmd)->cmd_args[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        exit_clean(sh, 2);
    }
    if ((*cmd)->cmd_args[2])
    {
        ft_putstr_fd("bash: exit: too many arguments\n", 2);
        sh->last_status_code = 1;
        return (1);
    }
    code = ft_atol((*cmd)->cmd_args[1]);
    exit_clean(sh, (unsigned char)code);
    return (0);
    // printf("exit\n");
    // //ft_putstr_fd("exit", 2);
    // if (!cmd || !*cmd || !(*cmd)->cmd_args[1])
    //     exit_clean(sh, EXIT_SUCCESS);
    // if (!ft_atol((*cmd)->cmd_args[1]))
    // {
    //     ft_putstr_fd("bash: exit: ", 2);
    //     ft_putstr_fd((*cmd)->cmd_args[1], 2);
    //     ft_putstr_fd(": numeric argument required\n", 2);
    //     exit_clean(sh, 2);
    // }
    // exit_code = ft_atol((*cmd)->cmd_args[1]);
    // //printf("exit code: %d\n", exit_code);
    // if (exit_code < 0)
    //     exit_code += 256; // Ensure exit code is in the range 0-255
    // if ((*cmd)->cmd_args[2])
    // {
    //     ft_putstr_fd("bash: exit: too many arguments\n", 2);
    //     return (1);
    // }
    // exit_clean(sh, exit_code);
}
