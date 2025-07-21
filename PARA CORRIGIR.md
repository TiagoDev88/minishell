home/tfilipe-/CommonCore/minishell$ export a a=b a+=c
/home/tfilipe-/CommonCore/minishell$ 
==397746== 
==397746== HEAP SUMMARY:
==397746==     in use at exit: 208,235 bytes in 223 blocks
==397746==   total heap usage: 709 allocs, 486 frees, 243,329 bytes allocated
==397746== 
==397746== 2 bytes in 1 blocks are definitely lost in loss record 1 of 64
==397746==    at 0x4848889: malloc (in /sgoinfre/tfilipe-/.brew/Cellar/valgrind/3.25.0/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==397746==    by 0x40754D: ft_strdup (in /home/tfilipe-/CommonCore/minishell/minishell)
==397746==    by 0x402D63: update_export_env (export_utils.c:80)
==397746==    by 0x402EAE: is_update_or_add_env (export_utils.c:122)
==397746==    by 0x40207B: ft_export (export.c:82)
==397746==    by 0x405FA1: execute (executor_built_ins.c:60)
==397746==    by 0x406100: exec_built_in (executor_built_ins.c:88)
==397746==    by 0x4049F8: execute_command (executor_command.c:125)
==397746==    by 0x404293: exec_line (executor.c:132)
==397746==    by 0x404394: executor (executor.c:172)
==397746==    by 0x4026AC: main (main.c:94)
==397746== 
==397746== LEAK SUMMARY:
==397746==    definitely lost: 2 bytes in 1 blocks
==397746==    indirectly lost: 0 bytes in 0 blocks
==397746==      possibly lost: 0 bytes in 0 blocks
==397746==    still reachable: 0 bytes in 0 blocks
==397746==         suppressed: 208,233 bytes in 222 blocks
==397746== 
==397746== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
--397746-- 
--397746-- used_suppression:     62 leak readline readline.supp:2 suppressed: 204,217 bytes in 221 blocks
--397746-- used_suppression:      1 leak add_history readline.supp:8 suppressed: 4,016 bytes in 1 blocks
==397746== 
==397746== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)




/home/tfilipe-/CommonCore/minishell$ wc << eof
> ^\  
> ^C
/home/tfilipe-/CommonCore/minishell$ echo a
> ^C
/home/tfilipe-/CommonCore/minishell$ ^C
/home/tfilipe-/CommonCore/minishell$ ^C
/home/tfilipe-/CommonCore/minishell$ ^C
/home/tfilipe-/CommonCore/minishell$ ^C
/home/tfilipe-/CommonCore/minishell$ ^C
/home/tfilipe-/CommonCore/minishell$ wc << eof
> ^C
/home/tfilipe-/CommonCore/minishell$ j
> eof
==399915== Memcheck, a memory error detector
==399915== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==399915== Using Valgrind-3.25.0 and LibVEX; rerun with -h for copyright info
==399915== Command: /usr/bin/wc
==399915== 
 4  6 20
==399915== 
==399915== HEAP SUMMARY:
==399915==     in use at exit: 0 bytes in 0 blocks
==399915==   total heap usage: 47 allocs, 47 frees, 15,291 bytes allocated
==399915== 
==399915== All heap blocks were freed -- no leaks are possible
==399915== 
==399915== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
/home/tfilipe-/CommonCore/minishell$ cat << eof
> ola^C
/home/tfilipe-/CommonCore/minishell$ eof
==399919== Memcheck, a memory error detector
==399919== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==399919== Using Valgrind-3.25.0 and LibVEX; rerun with -h for copyright info
==399919== Command: /usr/bin/cat
==399919== 
==399919== 
==399919== HEAP SUMMARY:
==399919==     in use at exit: 0 bytes in 0 blocks
==399919==   total heap usage: 31 allocs, 31 frees, 139,232 bytes allocated
==399919== 
==399919== All heap blocks were freed -- no leaks are possible
==399919== 
==399919== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
/home/tfilipe-/CommonCore/minishell$ 

















