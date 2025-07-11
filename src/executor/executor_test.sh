#!/bin/bash

res_errors=0
exit_code_errors=0
file_errors=0

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

run_rw_test()
{
	local input="$1"
	local test_file="$2"
	bash_test_file="$2_"

    BASH_OUT=$(bash -c "$input"_ 2>&1)
	BASH_EXIT_CODE=$(echo $?)
    MINI_OUT=$(../../minishell <<< "$input" 2>&1)
	MINI_EXIT_CODE=$(echo $?)
	FILES_DIFF=$(diff $test_file $bash_test_file)

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

	if [[ -z "$FILES_DIFF" ]]; then
		echo "✅ File: OK"
	else
		echo "❌ File: KO"
		((file_errors++))
	fi

    echo "----------------------------"

	echo ""
}

run_rw_test()
{
	local input="$1"
	local test_file="$2"
	bash_test_file="$2_"

    BASH_OUT=$(bash -c "$input"_ 2>&1)
	BASH_EXIT_CODE=$(echo $?)
    MINI_OUT=$(../../minishell <<< "$input" 2>&1)
	MINI_EXIT_CODE=$(echo $?)
	FILES_DIFF=$(diff $test_file $bash_test_file)

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

	if [[ -z "$FILES_DIFF" ]]; then
		echo "✅ File: OK"
	else
		echo "❌ File: KO"
		((file_errors++))
	fi

    echo "----------------------------"

	echo ""
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

run_read_write_files_test()
{
	echo "              Read/write files"
	echo ""

	run_rw_test "ls > executor_tests/rw_tests/1" "executor_tests/rw_tests/1"
	run_rw_test "cat executor_tests/rw_tests/1 > executor_tests/rw_tests/2" "executor_tests/rw_tests/2"
	run_rw_test "cat < executor_tests/rw_tests/2 | grep banana > executor_tests/rw_tests/3" "executor_tests/rw_tests/3"
	run_rw_test "cat executor_tests/rw_tests/3 | wc -l | cat > executor_tests/rw_tests/4" "executor_tests/rw_tests/4"
	run_rw_test "cat < executor_tests/rw_tests/4" "executor_tests/rw_tests/4"
	run_rw_test "echo "4" | cat >> executor_tests/rw_tests/4" "executor_tests/rw_tests/4"
	rm executor_tests/rw_tests/*
	echo ""
}

run_heredoc_test()
{
	echo "              Read/write files"
	echo ""

	run_hdoc_test "executor_tests/heredoc_tests/1" "Hello" "   World" "E" "EOF" "EOF"
	run_hdoc_test "executor_tests/heredoc_tests/2" "Hello" "   World" "eof" "EOF" "EOF"
	run_hdoc_test "executor_tests/heredoc_tests/3" "Hello" "   World" "eo" "EOF" "EOF"
	rm executor_tests/rw_heredoc/*
	echo ""
}


echo "---------- Minishell tester ----------"
echo ""
echo ""
make test -C ../../ > /dev/null

run_simple_cmds
run_cmds_with_flags
run_cmds_with_pipes
run_read_write_files_test

echo "Result errors: $res_errors"
echo "Exit code errors: $exit_code_errors"
echo "File errors: $file_errors"
make fclean -C ../../ > /dev/null
