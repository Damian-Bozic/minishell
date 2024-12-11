/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:06:10 by amasiuk           #+#    #+#             */
/*   Updated: 2024/12/02 09:11:20 by amasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	string_state_lexer(char **cmd, t_lex_state *state, t_list **tokens)
{
	// ft_printf("entering string state lexer\n");

	transist(state, **cmd);
	if (**cmd == '|')
		ft_lstadd_back(tokens, new_lexer_token(T_PIPE, NULL));
	else if (**cmd == '>' && *((*cmd) + 1) == '>')
	{
		ft_lstadd_back(tokens, new_lexer_token(T_APPEND, NULL));
		(*cmd)++;
	}
	else if (**cmd == '>')
		ft_lstadd_back(tokens, new_lexer_token(T_REDIR_OUT, NULL));
	else if (**cmd == '<' && *((*cmd) + 1) == '<')
	{
		ft_lstadd_back(tokens, new_lexer_token(T_HEREDOC, NULL));
		(*cmd)++;
	}
	else if (**cmd == '<')
		ft_lstadd_back(tokens, new_lexer_token(T_REDIR_IN, NULL));
	else if (!ft_strchr(" '\"", **cmd))
		append_lexer_token(tokens, *cmd);
	(*cmd)++;
}

static void	quotes_state_lexer(char **cmd, t_lex_state *state, t_list **tokens,
		char qtype)
{
	transist(state, **cmd);
	if (qtype == '"' && !ft_strchr("\"", **cmd))
		append_lexer_token(tokens, *cmd);
	else if (qtype == '\'' && **cmd != '\'')
		append_lexer_token(tokens, *cmd);
	(*cmd)++;
}

static void	initial_state_lexer(char **cmd, t_lex_state *state, t_list **tokens)
{
	// ft_printf("initial state lexer\n");
	transist(state, **cmd);
	// ft_printf("transist checked\n");
	if (ft_strchr("'\"", **cmd))
		ft_lstadd_back(tokens, new_lexer_token(T_STRING, ft_strdup("")));
	else if (**cmd == '|')
		ft_lstadd_back(tokens, new_lexer_token(T_PIPE, NULL));
	else if (**cmd == '>' && *((*cmd) + 1) == '>')
		ft_lstadd_back(tokens, new_lexer_token(T_APPEND, NULL));
	else if (**cmd == '>')
		ft_lstadd_back(tokens, new_lexer_token(T_REDIR_OUT, NULL));
	else if (**cmd == '<' && *((*cmd) + 1) == '<')
		ft_lstadd_back(tokens, new_lexer_token(T_HEREDOC, NULL));
	else if (**cmd == '<')
		ft_lstadd_back(tokens, new_lexer_token(T_REDIR_IN, NULL));
	else if (**cmd != ' ')
		ft_lstadd_back(tokens, new_lexer_token(T_STRING, ft_substr(*cmd, 0,
					1)));
	if ((**cmd == '>' && *((*cmd) + 1) == '>') || (**cmd == '<' && *((*cmd)
				+ 1) == '<'))
		(*cmd)++;
	(*cmd)++;
	// ft_printf("end of initial state lexer\n");
}

t_list	*lexer_analysis(char *input)
{
	t_lex_state	current_state;
	t_list		*token_list;

	current_state = L_INIT;
	token_list = NULL;
	// ft_printf("lexer_analysis start\n");
	while (*input)
	{
		// ft_printf("lexer loop state == %d\n", current_state);
		// ft_printf("lexer loop taking input %s\n", input);
		if (current_state == L_INIT)
			initial_state_lexer(&input, &current_state, &token_list);
		else if (current_state == L_QUOTE)
			quotes_state_lexer(&input, &current_state, &token_list, '\'');
		else if (current_state == L_DQUOTE)
			quotes_state_lexer(&input, &current_state, &token_list, '\"');
		else
			string_state_lexer(&input, &current_state, &token_list);
	}
	// ft_printf("lexer loop end\n");
	if (current_state == L_QUOTE || current_state == L_DQUOTE)
	{
		db_nerror("lexer syntax error quote not closed");
		return (free_lexer_token_data(&token_list), NULL);
	}
	return (token_list);
}
