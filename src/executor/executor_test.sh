#!/bin/bash

res_errors=0
exit_code_errors=0

run_cmds_test() {
    local input="$1"

    BASH_OUT=$(bash -c "$input" 2>&1)
	BASH_EXIT_CODE=$(echo $?)
    MINI_OUT=$(../../minishell <<< "$input" 2>&1)
	MINI_EXIT_CODE=$(echo $?)

    echo "Testing:   $input"

	if [[ "$BASH_OUT" == "$MINI_OUT" ]]; then
		echo "✅ Result: OK"
	else
		echo "❌ Result: KO"
		((res_errors++))
	fi

	if [[ "$BASH_EXIT_CODE" == "$MINI_EXIT_CODE" ]]; then
		echo "✅ Exit code: OK"
	else
		echo "❌ Exit code: KO"
		((exit_code_errors++))
	fi
    echo "----------------------------"
}

run_simple_cmds()
{
	echo "              Simple commands"
	echo ""

	run_cmds_test "ls"
	run_cmds_test "whoami"
	run_cmds_test "date"
	run_cmds_test "uname"
	run_cmds_test "hostname"
	run_cmds_test "id"

	echo ""

}

run_cmds_with_flags()
{
	echo "              Commands with flags"
	echo ""

	run_cmds_test "ls -l"
	run_cmds_test "ls -a"
	run_cmds_test "find /tmp . -type f"
	run_cmds_test "find . -maxdepth 1"
	run_cmds_test "grep banana executor_tests/test_files/simple_file.txt"
	run_cmds_test "grep -i banana executor_tests/test_files/simple_file.txt"
	run_cmds_test "grep -n banana executor_tests/test_files/simple_file.txt"
	run_cmds_test "wc executor_tests/test_files/simple_file.txt"
	run_cmds_test "wc -l executor_tests/test_files/simple_file.txt"
	run_cmds_test "wc -w executor_tests/test_files/simple_file.txt"
	run_cmds_test "head -n 2 executor_tests/test_files/simple_file.txt"
	run_cmds_test "tail -n 3 executor_tests/test_files/simple_file.txt"
	run_cmds_test "date +"%Y-%m-%d %H:%M:%S""
	run_cmds_test "id -u"
	run_cmds_test "id -un"

	echo ""
}

run_cmds_with_pipes()
{
	echo "              Commands with pipes"
	echo ""

	run_cmds_test "ls | cat"
	run_cmds_test "ls -la | grep "4096""
	run_cmds_test "cat executor_tests/test_files/simple_file.txt | grep banana"
	run_cmds_test "echo 'Hello              World' | wc -c"
	run_cmds_test "cat executor_tests/test_files/simple_file.txt | wc -l | cat"
	run_cmds_test "cat executor_tests/test_files/simple_file.txt | cat "
	run_cmds_test "seq 1 100 | grep '[13579]$' | sort -n | wc -l"
	run_cmds_test "ls -l /usr/bin | grep '^-' | cut -d' ' -f1 | head -n 5"
	run_cmds_test "cat executor_tests/test_files/simple_file.txt | tr ' ' '\n' | sort | uniq -c | sort -nr"
	run_cmds_test "seq 1 50 | awk '{print $1*$1}' | grep -E '^[0-9]{2}$' | wc -l"
	run_cmds_test "du -ah . | sort -rh | head -n 10"
	run_cmds_test "find . -name '*.c' | rev | cut -d'/' -f1 | rev | sort"

	echo ""
}

echo "---------- Minishell tester ----------"
make test -C ../../ > /dev/null

run_simple_cmds
run_cmds_with_flags
run_cmds_with_pipes

echo "Result errors: $res_errors"
echo "Exit code errors: $exit_code_errors"
make fclean -C ../../ > /dev/null
