# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 15:52:49 by dbozic            #+#    #+#              #
#    Updated: 2024/12/16 03:29:56 by amasiuk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g
MAIN = minishell.c

# Source files
SOURCES = $(addprefix execution/, \
		envs_manager.c envs_split.c envs_utils.c execute_utils.c \
		execute.c ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c \
		ft_pwd.c ft_unset.c parser_env.c pipex.c variable_expansion.c) \
		$(addprefix lexer_parser/, \
		free_command_list.c heredoc.c lexer_states.c parser_actions.c \
		parser_analizer.c parser_states.c signals.c token_actions.c) \
		helper_functions/db_error.c \
		helper_functions/print_errors.c  \
		

OBJECTS = $(SOURCES:%.c=%.o)
NAME = minishell.a
PROGRAM = minishell
LIBFT = Libft/libft.a

# Include directories
INCLUDES = -I. -I Libft -I /Users/${USER}/.brew/opt/readline/include -I src

# Targets
all: $(PROGRAM)

$(LIBFT):
	$(MAKE) -C Libft

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

$(PROGRAM): $(LIBFT) $(NAME)
	$(CC) $(FLAGS) $(MAIN) $(NAME) $(LIBFT) -lreadline -o $(PROGRAM)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C Libft clean

fclean: clean
	rm -f $(NAME) $(PROGRAM)
	$(MAKE) -C Libft fclean

re: fclean all

full: all clean
	clear
