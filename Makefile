# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 10:49:43 by hyojlee           #+#    #+#              #
#    Updated: 2022/04/19 17:00:15 by hyojlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lncurses -lreadline -L/Users/hyojlee/.brew/opt/readline/lib
CPPFLAGS = -I/Users/hyojlee/.brew/opt/readline/include
INC = ./includes
NAME = minishell
MAKE = make
LIB_NAME = libft.a
LIB_DIR = ./libft
SRC_DIR = ./sources
SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/list.c \
		$(SRC_DIR)/check.c	\
		$(SRC_DIR)/quotecheck.c	\
		$(SRC_DIR)/syntax.c	\
		$(SRC_DIR)/util.c
OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIB_DIR)/
	mv $(LIB_DIR)/$(LIB_NAME) $(LIB_NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -I$(INC) -o $(NAME) $(OBJS) $(LIB_NAME)

clean:
	$(MAKE) clean -C $(LIB_DIR)/
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIB_NAME)

re: fclean all

.PHONY: all clean fclean re
