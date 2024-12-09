/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:02:46 by dbozic            #+#    #+#             */
/*   Updated: 2024/09/19 15:02:50 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This is the main .h file

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"
# include "db_colours.h"

/*
 * Data structure for the shell environment.
 * Contains environment variables and command list, among other things.
 */

typedef struct s_envs
{
	char			*name;
	char			*contents;
	struct s_envs	*next;
}	t_envs;

typedef struct s_data
{
	char **env;           /* Environment variables */
	t_list *command_list; /* List of commands */
	t_envs *envs;
	int stdin_dup;        /* Duplicated standard input file descriptor */
	int stdout_dup;       /* Duplicated standard output file descriptor */
}		t_data;

# include "execution/execution.h"
# include "lexer_parser/lexer_parser.h"

void	free_ptr_ptr_array(char ***array);
void	free_ptr_array(char **ptr_array);
char	**db_dup_arr_of_str(char **array);

int		db_error(char *error_message, int error_code);
void	*db_nerror(char *error_message);

#endif
