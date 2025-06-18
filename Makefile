
NAME = minishell

CC = cc
CFLAGS =  -Wall -Wextra -Werror -I includes -I libft

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a


SRC_DIR = src
SRCS = src/main.c


OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "✅  $(NAME) Compiled successfully!"

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)
	@echo "clean: object files removed"

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "fclean: executable removed"


re: fclean all

.PHONY: all clean fclean re