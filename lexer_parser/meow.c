/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:34:27 by amasiuk           #+#    #+#             */
/*   Updated: 2024/11/06 14:34:45 by amasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Define a structure for storing words
typedef struct s_word
{
	char *cont;          // Content of the word
	char *type;          // String type of the word (e.g., command, argument)
	struct s_word *prev; // Pointer to the previous word
	struct s_word *next; // Pointer to the next word
}			t_word;

typedef struct s_split
{
	t_word *first; // Pointer to the first word
	t_word *last;  // Pointer to the last word
}			t_split;

// Function prototypes
void		ft_putendl_fd(char *s, int fd);
void		ft_bzero(void *s, size_t n);
void		skip_space(char *input, int *i);
t_word		*new_word(char *c, const char *type);
int			push_word(t_split *split, char *c, const char *type);
const char	*get_token_type(char *token);
void		handle_heredoc(char *delimiter, t_split *split);
int			split_words(char *input, t_split *split);
void		free_split(t_split *split);

// Function to output a string followed by a newline
void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		write(fd, s, strlen(s));
		write(fd, "\n", 1);
	}
}

// Function to zero out memory
void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}

// Signal handler for SIGINT (Ctrl+C)
static void	new_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// Set signals for interactive mode
void	set_interactive_signals(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	ft_bzero(&sigint_act, sizeof(sigint_act));
	sigint_act.sa_handler = &new_prompt;
	sigaction(SIGINT, &sigint_act, NULL);
	ft_bzero(&sigquit_act, sizeof(sigquit_act));
	sigquit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigquit_act, NULL);
}

// Set signals for non-interactive mode
void	set_non_interactive_signals(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

// Handle heredoc input
void	handle_heredoc(char *delimiter, t_split *split)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> "); // Prompt for heredoc input
		// Check if the delimiter is reached
		if (line == NULL || (delimiter && strcmp(line, delimiter) == 0))
		{
			free(line);
			break ;
		}
		// Add the input to the structure
		if (!push_word(split, line, "HEREDOC"))
		{
			printf("Error adding heredoc content.\n");
			free(line);
			break ;
		}
		free(line);
	}
}

// Function to split input string into words
int	split_words(char *input, t_split *split)
{
	char		*token;
	const char	*type;

	token = strtok(input, " ");
	while (token != NULL)
	{
		type = get_token_type(token); // Determine the type of the token
		if (!push_word(split, token, type))
		{
			return (0);
		}
		// If we encounter a heredoc, handle it
		if (strcmp(type, "ARGUMENT") == 0 && strcmp(token, "<<") == 0)
		{
			token = strtok(NULL, " ");
			if (token != NULL)
			{
				push_word(split, token, "DELIMITER");
				handle_heredoc(token, split);
			}
			break ;
		}
		token = strtok(NULL, " ");
	}
	return (1);
}

// Function to get the string type of a token
const char	*get_token_type(char *token)
{
	if (strcmp(token, "cat") == 0)
	{
		return ("COMMAND");
	}
	else if (strcmp(token, "<<") == 0)
	{
		return ("ARGUMENT");
	}
	else if (strcmp(token, "|") == 0)
	{
		return ("PIPE");
	}
	return ("STRING");
}

// Function to create a new word in the list
t_word	*new_word(char *c, const char *type)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->cont = strdup(c);
	word->type = strdup(type); // Use string type instead of numeric
	word->prev = NULL;
	word->next = NULL;
	return (word);
}

// Function to add a word to the structure
int	push_word(t_split *split, char *c, const char *type)
{
	t_word	*word;

	word = new_word(c, type);
	if (!word)
		return (0);
	if (!split->first)
	{
		split->first = word;
		split->last = word;
	}
	else
	{
		split->last->next = word;
		word->prev = split->last;
		split->last = word;
	}
	return (1);
}

// Function to free the memory of the split structure
void	free_split(t_split *split)
{
	t_word	*current;
	t_word	*next;

	current = split->first;
	while (current)
	{
		next = current->next;
		free(current->cont);
		free(current->type);
		free(current);
		current = next;
	}
	free(split);
}

// Main function
int	main(void)
{
	char	*input;
	int		is_interactive;
	t_split	*split;
	t_word	*word;

	// Check for interactive mode
	is_interactive = isatty(STDIN_FILENO);
	if (is_interactive)
	{
		set_interactive_signals();
	}
	else
	{
		set_non_interactive_signals();
	}
	// Main input loop
	while (1)
	{
		input = readline("myshell> ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (input && *input)
		{
			add_history(input);
		}
		// Split input into words and check for heredoc
		split = malloc(sizeof(t_split));
		ft_bzero(split, sizeof(t_split));
		if (split_words(input, split))
		{
			word = split->first;
			while (word)
			{
				printf("Type: %s, Content: %s\n", word->type, word->cont);
				word = word->next;
			}
		}
		free_split(split);
		free(input);
	}
	return (0);
}
 */