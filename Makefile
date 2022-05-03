# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 10:49:43 by hyojlee           #+#    #+#              #
#    Updated: 2022/05/03 17:48:06 by hyojlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g3 -fsanitize=address
# CFLAGS = -fsanitize=thread -g
# CFLAGS = -g
# CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lncurses -lreadline -L/Users/hyojlee/.brew/opt/readline/lib
CPPFLAGS = -I/Users/hyojlee/.brew/opt/readline/include
# LDFLAGS = -lncurses -lreadline -L/usr/local/opt/readline/lib
# CPPFLAGS = -I/usr/local/opt/readline/include
INC = ./includes
NAME = minishell
MAKE = make
LIB_NAME = libft.a
LIB_DIR = ./libft
SRC_DIR = ./sources
SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/list.c \
		$(SRC_DIR)/tokenize.c	\
		$(SRC_DIR)/quotecheck.c	\
		$(SRC_DIR)/syntax.c	\
		$(SRC_DIR)/astree.c	\
		$(SRC_DIR)/semantic.c	\
		$(SRC_DIR)/replace_env.c	\
		$(SRC_DIR)/replace_utils.c	\
		$(SRC_DIR)/env_list.c	\
		$(SRC_DIR)/builtin/exit.c	\
		$(SRC_DIR)/builtin/echo.c	\
		$(SRC_DIR)/builtin/env.c	\
		$(SRC_DIR)/builtin/cd.c	\
		$(SRC_DIR)/builtin/export.c	\
		$(SRC_DIR)/builtin/pwd.c	\
		$(SRC_DIR)/builtin/unset.c	\
		$(SRC_DIR)/util.c	\
		$(SRC_DIR)/redir.c	\
		$(SRC_DIR)/exec.c	\
		$(SRC_DIR)/ft_execve.c	\
		$(SRC_DIR)/get_argv.c
OBJS = $(SRCS:.c=.o)


all: $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -I$(INC) -c $^ -o $@

$(NAME): $(OBJS)
	$(MAKE) bonus -C $(LIB_DIR)/
	mv $(LIB_DIR)/$(LIB_NAME) $(LIB_NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -I$(INC) -o $(NAME) $(OBJS) $(LIB_NAME)

clean:
	$(MAKE) clean -C $(LIB_DIR)/
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIB_NAME)

re: fclean all

.PHONY: all clean fclean re
