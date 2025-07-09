#!/bin/bash

MINISHELL="./minishell"

passed=0
failed=0
test_number=1
failed_tests=()

run_test() {
  local input="$1"
  local expected="$2"
  local bash_expected="$3"

  output=$(echo "$input" | $MINISHELL)
  filtered_output=$(echo "$output" | grep -v '^/mnt/c/Users/foraa/Documents/Programacao/C/42school/minishell\$')
  #filtered_output=$(echo "$output" | grep -v '^/home/tfilipe-/CommonCore/minishell\$')
  filtered_output=$(echo "$filtered_output" | sed '/^$/d')

  echo -e "\n\033[1;34m[$test_number] Input:\033[0m $input"
  echo -e "\033[1;33mExpected (Bash tokens):\033[0m\n$bash_expected"
  echo -e "\033[1;32mGot (My minishell):\033[0m\n$filtered_output"

  if [ "$filtered_output" = "$expected" ]; then
    echo -e "\033[0;32mTest PASSED\033[0m"
    passed=$((passed + 1))
  else
    echo -e "\033[0;31mTest FAILED\033[0m"
    failed=$((failed + 1))
    failed_tests+=("[$test_number] $input")
  fi

  test_number=$((test_number + 1))
}



# ====== TESTES ======


# 1. Input simples
run_test "echo ola" \
"Token: [0] |echo|
Token: [0] |ola|" \
"echo ola"

# 2. Pipe simples
run_test "ls | grep foo" \
"Token: [0] |ls|
Token: [5] |||
Token: [0] |grep|
Token: [0] |foo|" \
"ls | grep foo"

# 3. Redirecionamento >
run_test "cat file > output.txt" \
"Token: [0] |cat|
Token: [0] |file|
Token: [1] |>|
Token: [0] |output.txt|" \
"cat file > output.txt"

# 4. Redirecionamento >>
run_test "echo foo >> log.txt" \
"Token: [0] |echo|
Token: [0] |foo|
Token: [3] |>>|
Token: [0] |log.txt|" \
"echo foo >> log.txt"

# 5. Heredoc <<
run_test "echo foo << EOF" \
"Token: [0] |echo|
Token: [0] |foo|
Token: [4] |<<|
Token: [0] |EOF|" \
"echo foo << EOF"

# 6. Aspas simples vazias
run_test "echo ''" \
"Token: [0] |echo|
Token: [0] ||" \
"echo ''"

# 7. Variável de ambiente
run_test "echo $USER" \
"Token: [0] |echo|
Token: [0] |$USER|" \
"echo \$USER"

# 8. Espaços a mais entre comandos
run_test "  echo    spaced   " \
"Token: [0] |echo|
Token: [0] |spaced|" \
"echo spaced"

# 9. Variáveis coladas e entre aspas
run_test "echo ola\$USER\$USER'\$USER'OLA" \
"Token: [0] |echo|
Token: [0] |ola$USER$USER\$USEROLA|" \
"echo ola\$USER\$USER'\$USER'OLA"

# 10. Variável entre aspas simples (não expande)
run_test "echo '\$USER'" \
"Token: [0] |echo|
Token: [0] |\$USER|" \
"echo '\$USER'"

# 11. Divisão entre aspas e fora
run_test 'echo "$USE"R' \
"Token: [0] |echo|
Token: [0] |R|" \
'echo "$USE"R'

# 12. Variável entre aspas duplas
run_test 'echo "$USER"' \
"Token: [0] |echo|
Token: [0] |$USER|" \
'echo "$USER"'

# 13. Várias aspas simples e duplas
run_test "echo 'foo''bar'\"baz\"" \
"Token: [0] |echo|
Token: [0] |foobarbaz|" \
"echo 'foo''bar'\"baz\""

# 14. Texto colado com $USER
run_test 'echo hello$USERworld' \
"Token: [0] |echo|
Token: [0] |hello|" \
'echo hello$USERworld'

# 15. Comando com $USER
run_test 'echo $USER' \
"Token: [0] |echo|
Token: [0] |$USER|" \
'echo $USER'

# 16. Comando com $HOME
run_test 'echo $HOME' \
"Token: [0] |echo|
Token: [0] |$HOME|" \
'echo $HOME'

# 17. Comando com $USER e $HOME
run_test 'echo $USER $HOME' \
"Token: [0] |echo|
Token: [0] |$USER|
Token: [0] |$HOME|" \
'echo $USER $HOME'

# 18. Comando com $USER e $HOME entre aspas
run_test 'echo "$USER" "$HOME"' \
"Token: [0] |echo|
Token: [0] |$USER|
Token: [0] |$HOME|" \
'echo "$USER" "$HOME"'

# 19. Comando com $USER e $HOME entre aspas simples
run_test 'echo '\''$USER'\'' '\''$HOME'\''' \
"Token: [0] |echo|
Token: [0] |\$USER|
Token: [0] |\$HOME|" \
'echo '\''$USER'\'' '\''$HOME'\'''

# 20. Comando com $ no nome
run_test '$USER$HOME' \
"Token: [0] |$USER$HOME|" \
'$USER$HOME'

# 21. Comando com $USER e $HOME
run_test 'echo $USER$HOME' \
"Token: [0] |echo|
Token: [0] |$USER$HOME|" \
'echo $USER$HOME'

# 22. Comando com $USER e $HOME entre aspas
run_test 'echo "$USER$HOME"' \
"Token: [0] |echo|
Token: [0] |$USER$HOME|" \
'echo "$USER$HOME"'

# 23. Comando com $USER e $HOME entre aspas simples
run_test 'echo '\''$USER$HOME'\''' \
"Token: [0] |echo|
Token: [0] |\$USER\$HOME|" \
'echo '\''$USER$HOME'\'''

# 24. Comando com $USER e $HOME entre aspas simples e duplas
run_test 'echo '\''$USER'\''"'"$HOME"'"' \
"Token: [0] |echo|
Token: [0] |\$USER/home/foraalinux|" \
'echo '\''$USER'\''"'"$HOME"'"'

# 25. Comando com $USER e $HOME entre aspas simples e duplas, sem espaço
run_test 'echo '\''$USER'\''"'"$HOME"'"' \
"Token: [0] |echo|
Token: [0] |\$USER$HOME|" \
'echo '\''$USER'\''"'"$HOME"'"'

# 26. Simples entre aspas simples
run_test "echo 'testando'" \
"Token: [0] |echo|
Token: [0] |testando|" \
"echo 'testando'"

# 27. Simples entre aspas duplas
run_test "echo \"testando\"" \
"Token: [0] |echo|
Token: [0] |testando|" \
"echo \"testando\""

# 28. Aspas duplas vazias coladas
run_test "echo \"\"\"\"" \
"Token: [0] |echo|
Token: [0] ||" \
"echo \"\"\"\""

# 29. Aspas simples + aspas duplas
run_test "echo '\"'" \
"Token: [0] |echo|
Token: [0] |\"|" \
"echo '\"'"

# 30. Aspas duplas + aspas simples
run_test "echo \"'\"" \
"Token: [0] |echo|
Token: [0] |'|" \
"echo \"'\""

# 31. Aspas simples + aspas duplas vazias
run_test "echo ''\"\"" \
"Token: [0] |echo|
Token: [0] ||" \
"echo ''\"\""

# 32. Aspas simples + aspas duplas juntas
run_test "echo ''\"\"" \
"Token: [0] |echo|
Token: [0] ||" \
"echo ''\"\""

# 33. Texto colado: aspas simples, duplas e sem aspas
run_test "echo foo'bar'baz\"qux\"" \
"Token: [0] |echo|
Token: [0] |foobarbazqux|" \
"echo foo'bar'baz\"qux\""

# 34. Texto colado: aspas simples, duplas e sem aspas, com variável
run_test "echo foo'bar'$USER\"baz\"" \
"Token: [0] |echo|
Token: [0] |foobarforaalinuxbaz|" \
"echo foo'bar'$USER\"baz\""

# 35. Variável entre aspas simples e texto colado
run_test "echo '\$USER'foo" \
"Token: [0] |echo|
Token: [0] |\$USERfoo|" \
"echo '$USER'foo"

# 36. Variável entre aspas duplas e texto colado
run_test "echo \"$USER\"foo" \
"Token: [0] |echo|
Token: [0] |foraalinuxfoo|" \
"echo \"$USER\"foo"

# 37. Variável com escape dentro de aspas simples
run_test "echo '\$USER'" \
"Token: [0] |echo|
Token: [0] |\$USER|" \
"echo '\$USER'"

# 38. Variável com escape dentro de aspas duplas
run_test "echo \"foo\\\$USER\"" \
"Token: [0] |echo|
Token: [0] |foo\\$USER|" \
"echo \"foo\\\$USER\""

# 39. Variável com escape fora de aspas
run_test "echo foo\\$USER" \
"Token: [0] |echo|
Token: [0] |foo\\$USER|" \
"echo foo\$USER"

# 40. Variável colada com texto entre aspas simples
run_test "echo $USER'foo'$HOME" \
"Token: [0] |echo|
Token: [0] |foraalinuxfoo$HOME|" \
"echo $USER'foo'$HOME"

# 41. Texto colado entre aspas simples e duplas alternadas
run_test "echo 'foo'\"bar\"'baz'" \
"Token: [0] |echo|
Token: [0] |foobarbaz|" \
"echo 'foo'\"bar\"'baz'"

# 42. Linha vazia
run_test "" \
"" \
""

# 43. Apenas espaços
run_test "    " \
"" \
""

# 44. Variável não definida
run_test "echo \$UNDEFINED_VAR" \
"Token: [0] |echo|
Token: [0] |$UNDEFINED_VAR|" \
"echo \$UNDEFINED_VAR"

# 45. Variável dentro de comando
run_test "$USER echo" \
"Token: [0] |$USER|
Token: [0] |echo|" \
"$USER echo"

# 46. Variável entre aspas e texto junto
run_test "echo \"$USER\"world" \
"Token: [0] |echo|
Token: [0] |foraalinuxworld|" \
"echo \"$USER\"world"

# 47. Variável dentro de aspas simples seguida de aspas duplas
run_test "echo '\$USER'\"world\"" \
"Token: [0] |echo|
Token: [0] |\$USERworld|" \
"echo '\$USER'\"world\""

# 48. Variável dentro de aspas duplas seguida de aspas simples
run_test "echo \"$USER\"'world'" \
"Token: [0] |echo|
Token: [0] |foraalinuxworld|" \
"echo \"$USER\"'world'"

# 49. Variável com escape dentro de aspas simples
run_test "echo '\$USER'" \
"Token: [0] |echo|
Token: [0] |\$USER|" \
"echo '\$USER'"

# 50. Variável com escape fora de aspas simples
run_test "echo \$USER" \
"Token: [0] |echo|
Token: [0] |$USER|" \
"echo \$USER"

# 51. Variável com escape dentro de aspas duplas
run_test "echo \"\$USER\"" \
"Token: [0] |echo|
Token: [0] |$USER|" \
"echo \"\$USER\""

# 52. Variável com escape fora de aspas duplas
run_test "echo \$USER" \
"Token: [0] |echo|
Token: [0] |$USER|" \
"echo \$USER"




echo -e "\n\033[1;35m===== TESTES FINALIZADOS =====\033[0m"
echo "Total de testes: $((passed + failed))"
echo -e "\033[0;32mPassaram: $passed\033[0m"
echo -e "\033[0;31mFalharam: $failed\033[0m"

if [ $failed -gt 0 ]; then
  echo -e "\n\033[1;31mTestes que falharam (ordenados):\033[0m"
  for test in "${failed_tests[@]}"; do
    echo "$test"
  done | sort -n
fi


