# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbozic <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 15:52:49 by dbozic            #+#    #+#              #
#    Updated: 2024/06/19 15:52:52 by dbozic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror
MAIN = minishell.c
SOURCES = 
OBJECTS = $(SOURCES:%.c=%.o)
NAME = minishell.a
PROGRAM = minishell
LIBFT = Libft/libft.a

all: $(PROGRAM)

$(LIBFT):
	$(MAKE) -C Libft

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

$(PROGRAM): $(MINILIBX) $(LIBFT) $(NAME)
	$(CC) $(FLAGS) $(MAIN) $(NAME) $(LIBFT) -lreadline -o $(PROGRAM)

%.o: %.c
	$(CC) $(FLAGS) -I. -o $@ -c $<

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C Libft clean

fclean: clean
	rm -f $(NAME) $(PROGRAM) $(BPROGRAM)
	$(MAKE) -C Libft fclean

cc:
	$(CC) $(FLAGS) $(MAIN) $(NAME) $(LIBFT) -lreadline -o $(PROGRAM)

re: fclean all


full: all clean
	clear
