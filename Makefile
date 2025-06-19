
NAME = minishell

CC = cc
CFLAGS =  -Wall -Wextra -Werror -I includes -I libft

LDFLAGS = -lreadline

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a


SRC_DIR = src

SRC_BUILTIN	=	$(addprefix builtins/, cd.c echo.c env.c exit.c export.c pwd.c unset.c)
SRC_MAIN	=	main.c
SRC_EXECUTOR =	$(addprefix executor/, executor.c)
SRC_UTILS	=	$(addprefix utils/, utils.c)
SRC_PARSER =	$(addprefix parser/, parser.c)
SRC_TOKENS =	$(addprefix tokens/, token.c)

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_BUILTIN) $(SRC_MAIN) $(SRC_UTILS) $(SRC_PARSER) \
		$(SRC_EXECUTOR) $(SRC_TOKENS))

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "✅  $(NAME) Compiled successfully!"

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS)
	@echo "clean: object files removed"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "fclean: executable removed"


re: fclean all

.PHONY: all clean fclean re