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

int	ft_exit(t_cmd **cmd)
{
	int	exit_code;

	printf("exit\n");
	if (!cmd || !*cmd || !(*cmd)->cmd_args[1])
        exit(EXIT_SUCCESS);
	if (!ft_atoi((*cmd)->cmd_args[1]))
    {
        ft_putstr_fd("bash: exit: ", 2);
        ft_putstr_fd((*cmd)->cmd_args[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        //clean_cmds(cmd, 0);
        exit(EXIT_FAILURE);
    }
	exit_code = ft_atoi((*cmd)->cmd_args[1]);
	if ((*cmd)->cmd_args[2])
    {
        ft_putstr_fd("bash: exit: too many arguments\n", 2);
        return (1);
    }
	//clean_cmds(cmd, 0);
	exit(exit_code);
}
