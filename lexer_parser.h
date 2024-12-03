/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:46:41 by amasiuk           #+#    #+#             */
/*   Updated: 2024/12/02 09:54:47 by amasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_LEXER_H
# define PARSER_LEXER_H

#include "minishell.h"

/* =============================== LEXER =============================== */

/*
 * Token data structure.
 * Contains information about the token's name, value, and type.
 */
typedef struct s_token_data
{
	char *name;    /* Token name (e.g., command or argument) */
	char *value;   /* Token value */
	t_token token; /* Token type (e.g., string, redirect, pipe) */
}		t_token_data;

/*
 * Lexer states.
 * States the lexer can be in during tokenization.
 */
typedef enum e_lex_state
{
	L_INIT,   /* Initial state */
	L_STRING, /* In a string */
	L_QUOTE,  /* In a single-quoted string */
	L_DQUOTE  /* In a double-quoted string */
}		t_lex_state;

/*
 * Lexer token types.
 * Defines the types of tokens that the lexer will recognize.
 */
typedef enum e_token
{
	T_STRING,    /* Regular string */
	T_REDIR_IN,  /* Input redirection */
	T_REDIR_OUT, /* Output redirection */
	T_APPEND,    /* Output append */
	T_HEREDOC,   /* Heredoc */
	T_PIPE       /* Pipe */
}		t_token;

/* =============================== PARSER =============================== */

/*
 * Parser states.
 * States the parser can be in while analyzing tokens.
 */
typedef enum e_pars_state
{
	P_INIT,      /* Initial state */
	P_COMMAND,   /* Parsing a command */
	P_REDIR_IN,  /* Parsing input redirection */
	P_REDIR_OUT, /* Parsing output redirection */
	P_APPEND,    /* Parsing output append */
	P_HEREDOC,   /* Parsing heredoc */
	P_INVALID    /* Invalid state */
}		t_pars_state;

/*
 * Error types in parsing.
 * Defines possible errors that may occur during parsing.
 */
typedef enum e_error
{
	SYNTAX,    /* Syntax error */
	MALLOC,    /* Memory allocation error */
	NOT_FOUND, /* Token not found */
	NO_ERROR   /* No error */
}		t_error;

/*
 * Command data structure.
 * Holds information about a command, its arguments,
	and file descriptors for input/output.
 */
typedef struct s_command
{
	int ac;         /* Number of arguments */
	char **args;    /* Array of arguments */
	int in_fileno;  /* Input file descriptor */
	int out_fileno; /* Output file descriptor */
}		t_command;

/*
 * Data structure for the shell environment.
 * Contains environment variables and command list, among other things.
 */
typedef struct s_data
{
	char **env;           /* Environment variables */
	t_list *command_list; /* List of commands */
	char **export_env;    /* Exported environment variables */
	int stdin_dup;        /* Duplicated standard input file descriptor */
	int stdout_dup;       /* Duplicated standard output file descriptor */
}		t_data;

/* =============================== LEXER FUNCTIONS =============================== */

/*
 * Performs lexical analysis of the input string.
 * Returns a list of tokens.
 */
t_list	*lexer_analysis(char *input);

/*
 * Transitions the lexer state based on the current character.
 */
void	transist(t_lex_state *current_state, char ch_read);

/*
 * Appends a token to the list of tokens.
 */
void	append_lexer_token(t_list **tokens, char *cmd);

/*
 * Frees the memory allocated for a token.
 */
void	free_lexer_token_data(void *token);

/*
 * Creates a new token of the specified type and value.
 * Returns a pointer to the new token.
 */
t_list	*new_lexer_token(t_token token_type, char *value);

/* =============================== PARSER FUNCTIONS =============================== */

/*
 * Analyzes the list of tokens and parses them into commands.
 * Returns a list of commands.
 */
t_list	*parser_analysis(t_list *tokens_list, t_data *data);

/*
 * Transitions the parser state based on the current token.
 */
void	transist_parser(t_pars_state *current_state, t_token token);

/*
 * Handles errors during parsing.
 * Returns the type of error that occurred.
 */
t_error	error_states(t_list *tokens, t_pars_state *current, t_list **cmd_list,
			t_data *data);

/*
 * Initializes the parsing state.
 * Prepares the parser for parsing the tokens.
 */
t_error	init_state(t_list *tokens, t_pars_state *state, t_list **commands);

/*
 * Parses a command from the token list.
 */
t_error	command_state(t_list *tokens, t_pars_state *state, t_list **commands);

/*
 * Parses input redirection from the token list.
 */
t_error	redir_in_state(t_list #ifndef DB_COLOURS_H*tokens, t_pars_state *state, t_list **commands);

/*
 * Parses output redirection or append from the token list.
 */
t_error	redir_out_append_state(t_list *tokens, t_pars_state *state,
			t_list **cmds, bool is_append);

/*
 * Parses heredoc from the token list.
 */
t_error	heredoc_state(t_list *tokens, t_pars_state *state, t_list **cmds,
			t_data *data);

/*
 * Sets the input file descriptor for a command.
 */
t_error	set_stdin(t_list *cmd_list, char *fname);

/*
 * Sets the output file descriptor for a command.
 */
t_error	set_stdout(t_list *cmd_list, char *fname, bool is_append);

/*
 * Appends a new argument to a command.
 */
t_error	append_command_arg(t_list *cmd_list, char *new_arg);

/*
 * Appends a new command to the list of commands.
 */
t_error	append_command(t_list **cmd_list, char *new_cmd);

/*
 * Frees the list of commands.
 */
void	free_command_list(t_list **command_list);

/*
 * Creates a heredoc for a command based on token value.
 */
t_error	create_heredoc(t_list *cmd_list, char *token_value, t_data *data);

#endif
