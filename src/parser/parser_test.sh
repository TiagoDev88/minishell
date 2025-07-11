#!/bin/bash

all_errors=0
all_tests=0
redir_n_tests=0
redir_errors=0
pipe_errors=0
pipe_n_tests=0

run_redirect_test() {
    local input="$1"

    BASH_ERROR=$(bash 2>&1 <<< "$input")
    BASH_ERROR=$(echo "$BASH_ERROR" | grep "syntax error")
    BASH_ERROR=$(echo "$BASH_ERROR" | sed 's/bash: line 1:/bash:/')

    MINI_ERROR=$(../../minishell 2>&1 <<< "$input")
    MINI_ERROR=$(echo "$MINI_ERROR" | grep "syntax error")

    echo "Testing: $input"
    echo "Bash:      $BASH_ERROR"
    echo "Minishell: $MINI_ERROR"

    if [[ "$BASH_ERROR" == "$MINI_ERROR" ]]; then
        echo "✅ OK"
    else
		((redir_errors++))
        echo "❌ KO"
    fi
	((redir_n_tests++))
    echo "----------------------------"
}

run_pipe_test() {
    local input="$1"

    BASH_ERROR=$(bash 2>&1 <<< "$input")
    BASH_ERROR=$(echo "$BASH_ERROR" | grep "syntax error")
    BASH_ERROR=$(echo "$BASH_ERROR" | sed 's/bash: line 1:/bash:/')

    MINI_ERROR=$(../../minishell 2>&1 <<< "$input")
    MINI_ERROR=$(echo "$MINI_ERROR" | grep "syntax error")

    echo "Testing: $input"
    echo "Bash:      $BASH_ERROR"
    echo "Minishell: $MINI_ERROR"

    if [[ "$BASH_ERROR" == "$MINI_ERROR" ]]; then
        echo "✅ OK"
    else
		((pipe_errors++))
        echo "❌ KO"
    fi
	((pipe_n_tests++))
    echo "----------------------------"
}

make -C ../../

echo "               --- Testing redirects ---"
echo ""
run_redirect_test ">>"
run_redirect_test "<"
run_redirect_test "<<"
run_redirect_test ">"
run_redirect_test "echo ola >"
run_redirect_test "echo ola <"
run_redirect_test "echo ola <<"
run_redirect_test "echo ola >>"
run_redirect_test "cat << EOF | > out <"
run_redirect_test "cat << EOF | > out >>"
run_redirect_test "cat << EOF | > out <<"
run_redirect_test "cat << EOF | > out >"
run_redirect_test "< in1 > out1 << in2 >> out2 <<"
run_redirect_test "<< in1 > out1 << in2 >> out2 <"
run_redirect_test "< in1 > out1 << in2 > out2 >>"
run_redirect_test "< in1 >> out1 << in2 >> out2 >"
run_redirect_test "cat << EOF | > "
run_redirect_test "cat << EOF | <"
run_redirect_test "cat << EOF | >>"
run_redirect_test "cat << EOF | <<"
run_redirect_test "cat << < "
run_redirect_test "cat << >"
run_redirect_test "cat << >>"
run_redirect_test "cat << <<"
run_redirect_test "cat >> < "
run_redirect_test "cat >> >"
run_redirect_test "cat >> >>"
run_redirect_test "cat >> <<"
run_redirect_test "cat < < "
run_redirect_test "cat < >"
run_redirect_test "cat < >>"
run_redirect_test "cat < <<"
run_redirect_test "cat > < "
run_redirect_test "cat > >"
run_redirect_test "cat > >>"
run_redirect_test "cat > <<"


echo ""
echo "Number of redirect tests made: $redir_n_tests"
if [[ "$redir_errors" == 0 ]]; then
    echo "Redirects: ✅ OK"
else
	echo "Redirects: ❌ KO"
fi

echo ""
echo "               --- Testing pipes ---"
run_pipe_test "|"
echo ""
echo "Number of pipe tests made: $pipe_n_tests"
if [[ "$pipe_errors" == 0 ]]; then
    echo "Pipes: ✅ OK"
else
	echo "Pipes: ❌ KO"
fi

echo ""
all_errors=$((redir_errors+pipe_errors))
all_tests=$((redir_n_tests+pipe_n_tests))

echo "Results: [$all_tests][$((all_tests-all_errors))]"
if [[ "$all_errors" == 0 ]]; then
	echo "All tests were sucessfull! ✅ OK"
else
	echo "You parser got errors! ❌ KO"
fi

echo ""

make fclean -C ../../ > /dev/null
