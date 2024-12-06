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
SOURCES = $(addprefix execution/, \
		ft_echo.c ft_pwd.c ft_cd.c ft_env.c ft_export.c ft_unset.c ft_env.c \
		ft_envs_util.c ft_doc_functions.c convert_envs_to_envp.c \
		ft_strjoin_mod.c filter_argv.c ft_getenv.c pipex.c exec_pipex.c \
		init_pipex.c ) \
		$(addprefix lexer_parser/, \
		free_command_list.c heredoc.c lexer_states.c parser_actions.c \
		parser_analizer.c parser_states.c signals.c token_actions.c ) \
		helper_functions/db_error.c helper_functions/freeing_functions.c
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

wf:
	$(CC) $(MAIN) $(NAME) $(LIBFT) -lreadline -o $(PROGRAM)

re: fclean all

full: all clean
	clear
