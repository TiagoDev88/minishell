#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 11:42:53 by tfilipe-          #+#    #+#              #
#    Updated: 2025/06/19 12:19:36 by tfilipe-         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = cc
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I.

SRCS =  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_printf_putchar.c ft_printf_putstr.c ft_printf.c ft_putnbr_base.c \
		ft_putnbr_unsigned.c ft_putnbr.c ft_putptr.c get_next_line_bonus.c \
		get_next_line_utils_bonus.c ft_atol.c

BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c

OBJS = $(SRCS:%.c=%.o)
BONUS_OBJS = $(BONUS_SRC:.c=.o)

RM = rm -f
AR = ar
ARFLAGS = rcs

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME):  $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo "✅ Libft Compiled successfully!"

bonus: $(OBJS) $(BONUS_OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "✅ Libft + Bonus Compiled successfully!"

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "clean Objects removed"

fclean: clean
	@$(RM) $(NAME)
	@echo "fclean Archive removed"

re: fclean all


.PHONY: all clean fclean re bonus