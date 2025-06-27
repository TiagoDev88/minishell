#!/bin/bash

MINISHELL="./minishell"

passed=0
failed=0
failed_tests=()


run_test() {
  local input="$1"
  local expected="$2"
  local bash_expected="$3"

  output=$(echo "$input" | $MINISHELL)
  filtered_output=$(echo "$output" | grep -v '^/mnt/c/Users/foraa/Documents/Programacao/C/42school/minishell\$')
  filtered_output=$(echo "$filtered_output" | sed '/^$/d')

  echo -e "\n\033[1;34mInput:\033[0m $input"
  echo -e "\033[1;33mExpected (Bash tokens):\033[0m\n$bash_expected"
  echo -e "\033[1;32mGot (My minishell):\033[0m\n$filtered_output"

  if [ "$filtered_output" = "$expected" ]; then
    echo -e "\033[0;32mTest PASSED\033[0m"
    passed=$((passed + 1))
  else
    echo -e "\033[0;31mTest FAILED\033[0m"
    failed=$((failed + 1))
    failed_tests+=("$input")
  fi
}


# ====== TESTES ======

# Input simples
run_test "echo ola" \
"Token: [0] |echo|
Token: [0] |ola|" \
"echo ola"

# Pipe simples
run_test "ls | grep foo" \
"Token: [0] |ls|
Token: [5] |||
Token: [0] |grep|
Token: [0] |foo|" \
"ls | grep foo"

# Redirecionamento >
run_test "cat file > output.txt" \
"Token: [0] |cat|
Token: [0] |file|
Token: [1] |>|
Token: [0] |output.txt|" \
"cat file > output.txt"

# Redirecionamento >>
run_test "echo foo >> log.txt" \
"Token: [0] |echo|
Token: [0] |foo|
Token: [3] |>>|
Token: [0] |log.txt|" \
"echo foo >> log.txt"

# Heredoc <<
run_test "echo foo << EOF" \
"Token: [0] |echo|
Token: [0] |foo|
Token: [4] |<<|
Token: [0] |EOF|" \
"echo foo << EOF"


# Aspas simples vazias
run_test "echo ''" \
"Token: [0] |echo|
Token: [0] ||" \
"echo ''"

# Variável de ambiente
run_test "echo $USER" \
"Token: [0] |echo|
Token: [0] |$USER|" \
"echo \$USER"


# Espaços a mais entre comandos
run_test "  echo    spaced   " \
"Token: [0] |echo|
Token: [0] |spaced|" \
"echo spaced"


# Variáveis coladas e entre aspas
run_test "echo ola\$USER\$USER'\$USER'OLA" \
"Token: [0] |echo|
Token: [0] |olaforaalinuxforaalinux\$USEROLA|" \
"echo ola\$USER\$USER'\$USER'OLA"


# Variável entre aspas simples (não expande)
run_test "echo '\$USER'" \
"Token: [0] |echo|
Token: [0] |\$USER|" \
"echo '\$USER'"

# Divisão entre aspas e fora
run_test 'echo "$USE"R' \
"Token: [0] |echo|
Token: [0] |R|" \
'echo "$USE"R'



# Variável entre aspas duplas
run_test 'echo "$USER"' \
"Token: [0] |echo|
Token: [0] |$USER|" \
'echo "$USER"'

# Várias aspas simples e duplas
run_test "echo 'foo''bar'\"baz\"" \
"Token: [0] |echo|
Token: [0] |foobarbaz|" \
"echo 'foo''bar'\"baz\""

# Texto colado com $USER
run_test 'echo hello$USERworld' \
"Token: [0] |echo|
Token: [0] |hello|" \
'echo hello$USERworld'

# Comando com $ no nome
run_test '$USER$HOME' \
"Token: [0] |$USER$HOME|" \
'$USER$HOME'


# Simples entre aspas simples
run_test "echo 'testando'" \
"Token: [0] |echo|
Token: [0] |testando|" \
"echo 'testando'"

# Simples entre aspas duplas
run_test "echo \"testando\"" \
"Token: [0] |echo|
Token: [0] |testando|" \
"echo \"testando\""

# Aspas simples vazias coladas
run_test "echo '''''" \
"Token: [0] |echo|
Token: [0] ||" \
"echo '''''"

# Aspas duplas vazias coladas
run_test "echo \"\"\"\"" \
"Token: [0] |echo|
Token: [0] ||" \
"echo \"\"\"\""

# Aspas simples + aspas duplas juntas
run_test "echo ''\"\"" \
"Token: [0] |echo|
Token: [0] ||" \
"echo ''\"\""

# Texto colado: aspas simples, duplas e sem aspas
run_test "echo foo'bar'baz\"qux\"" \
"Token: [0] |echo|
Token: [0] |foobarbazqux|" \
"echo foo'bar'baz\"qux\""

# Escape dentro de aspas duplas (o escape funciona)
run_test "echo \"foo\\\"bar\"" \
"Token: [0] |echo|
Token: [0] |foo\"bar|" \
"echo \"foo\\\"bar\""

# Escape dentro de aspas simples (escape não é interpretado)
run_test "echo 'foo\\'bar'" \
"Token: [0] |echo|
Token: [0] |foo\'bar|" \
"echo 'foo\'bar'"

# Variável com escape dentro de aspas duplas
run_test "echo \"foo\\\$USER\"" \
"Token: [0] |echo|
Token: [0] |foo\$USER|" \
"echo \"foo\\\$USER\""

# Variável com escape fora de aspas
run_test "echo foo\\$USER" \
"Token: [0] |echo|
Token: [0] |foo\\$USER|" \
"echo foo\$USER"

# Variável colada com texto entre aspas simples
run_test "echo $USER'foo'$HOME" \
"Token: [0] |echo|
Token: [0] |foraalinuxfoo/home/foraalinux|" \
"echo $USER'foo'$HOME"

# Texto colado entre aspas simples e duplas alternadas
run_test "echo 'foo'\"bar\"'baz'" \
"Token: [0] |echo|
Token: [0] |foobarbaz|" \
"echo 'foo'\"bar\"'baz'"

# Linha vazia
run_test "" \
"" \
""

# Apenas espaços
run_test "    " \
"" \
""

# Variável não definida
run_test "echo $UNDEFINED_VAR" \
"Token: [0] |echo|
Token: [0] |$UNDEFINED_VAR|" \
"echo \$UNDEFINED_VAR"

# Variável dentro de comando (não é token, apenas um comando estranho)
run_test "$USER echo" \
"Token: [0] |$USER|
Token: [0] |echo|" \
"$USER echo"

# Variável entre aspas e texto junto
run_test "echo \"$USER\"world" \
"Token: [0] |echo|
Token: [0] |foraalinuxworld|" \
"echo \"$USER\"world"

# Variável dentro de aspas simples seguida de aspas duplas
run_test "echo '\$USER'\"world\"" \
"Token: [0] |echo|
Token: [0] |\$USERworld|" \
"echo '\$USER'\"world\""


echo -e "\n\033[1;35m===== TESTES FINALIZADOS =====\033[0m"
echo "Total de testes: $((passed + failed))"
echo -e "\033[0;32mPassaram: $passed\033[0m"
echo -e "\033[0;31mFalharam: $failed\033[0m"

if [ $failed -gt 0 ]; then
  echo -e "\n\033[1;31mTestes que falharam (input):\033[0m"
  for test_input in "${failed_tests[@]}"; do
    echo "- $test_input"
  done
fi

