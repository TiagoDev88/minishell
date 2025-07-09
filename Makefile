
NAME = minishell

CC = cc
#CFLAGS = -Wall -Wextra -Werror -I includes -I libft
CFLAGS = -I includes -I libft 

LDFLAGS = -lreadline

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a


SRC_DIR = src

SRC_BUILTIN	=	$(addprefix builtins/, cd.c echo.c env.c exit.c export.c pwd.c unset.c)
SRC_MAIN	=	test_mai.c
SRC_EXECUTOR =	$(addprefix executor/, executor.c executor_cleaner.c executor_command.c \
							executor_errors.c executor_file_struct.c executor_heredoc.c \
							executor_path.c executor_pipe_struct.c executor_proccess_struct.c  \
							executor_validator.c)
SRC_UTILS	=	$(addprefix utils/, utils.c)
SRC_PARSER =	$(addprefix parser/, parser.c parser_cmd.c parser_cmd_utils.c parser_cleaner.c \
							parser_validator.c)
SRC_TOKENS =	$(addprefix tokens/, token.c token_handle_word.c init_structs.c)

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_BUILTIN) $(SRC_MAIN) $(SRC_UTILS) $(SRC_PARSER) \
		$(SRC_EXECUTOR) $(SRC_TOKENS))

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "✅  $(NAME) Compiled successfully!"

test: CFLAGS += -D TEST_MODE=1
test: re
	@echo "🧪 Compilado em modo de teste com -D TEST_MODE=1"

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS)
	@echo "clean: object files removed"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "fclean: executable removed"

re: fclean all

leaks: all readline.supp
	@valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --trace-children=yes -s ./minishell

readline.supp:
	echo '{' > readline.supp
	echo ' leak readline' >> readline.supp
	echo ' Memcheck:Leak' >> readline.supp
	echo ' ...' >> readline.supp
	echo ' fun:readline' >> readline.supp
	echo '}' >> readline.supp
	echo '{' >> readline.supp
	echo ' leak add_history' >> readline.supp
	echo ' Memcheck:Leak' >> readline.supp
	echo ' ...' >> readline.supp
	echo ' fun:add_history' >> readline.supp
	echo '}' >> readline.supp

.PHONY: all clean fclean re