# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 10:49:43 by hyojlee           #+#    #+#              #
#    Updated: 2022/05/17 16:46:10 by hyojlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
# CFLAGS = -g3 -fsanitize=address
# CFLAGS = -fsanitize=thread -g
# CFLAGS = -g
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lncurses -lreadline -L/Users/hyojlee/.brew/opt/readline/lib
CPPFLAGS = -I/Users/hyojlee/.brew/opt/readline/include
# LDFLAGS = -lncurses -lreadline -L/usr/local/opt/readline/lib
# CPPFLAGS = -I/usr/local/opt/readline/include

# LDFLAGS = -lncurses -lreadline -L/Users/yson/.brew/opt/readline/lib
# CPPFLAGS = -I/Users/yson/.brew/opt/readline/include

INC = ./includes
NAME = minishell
MAKE = make
LIB_NAME = libft.a
LIB_DIR = ./libft
SRC_DIR = ./sources
SRCS = $(SRC_DIR)/main.c 						\
		$(SRC_DIR)/builtin/cd.c					\
		$(SRC_DIR)/builtin/echo.c				\
		$(SRC_DIR)/builtin/env.c				\
		$(SRC_DIR)/builtin/exit.c				\
		$(SRC_DIR)/builtin/export.c				\
		$(SRC_DIR)/builtin/pwd.c				\
		$(SRC_DIR)/builtin/unset.c				\
		$(SRC_DIR)/exec/ft_execve.c				\
		$(SRC_DIR)/exec/get_cmd_opt.c			\
		$(SRC_DIR)/exec/heredoc/heredoc.c		\
		$(SRC_DIR)/exec/heredoc/heredoc_utils.c	\
		$(SRC_DIR)/exec/read_tree.c				\
		$(SRC_DIR)/exec/pipe.c					\
		$(SRC_DIR)/exec/redir.c					\
		$(SRC_DIR)/parsing/astree.c				\
		$(SRC_DIR)/parsing/astree_insert.c		\
		$(SRC_DIR)/parsing/env_list.c			\
		$(SRC_DIR)/parsing/list.c				\
		$(SRC_DIR)/parsing/replace_env.c		\
		$(SRC_DIR)/parsing/semantic.c			\
		$(SRC_DIR)/parsing/syntax.c				\
		$(SRC_DIR)/parsing/syntax_2.c			\
		$(SRC_DIR)/parsing/tokenize.c			\
		$(SRC_DIR)/utils/clear_utils.c			\
		$(SRC_DIR)/utils/free_utils.c			\
		$(SRC_DIR)/utils/print_utils.c			\
		$(SRC_DIR)/utils/replace_utils.c		\
		$(SRC_DIR)/utils/termios_utils.c		\
		$(SRC_DIR)/utils/utils.c								
		

OBJS = $(SRCS:.c=.o)

all: $(NAME)

# %.o:%.c
# 	@$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -I$(INC) -c $^ -o $@

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
