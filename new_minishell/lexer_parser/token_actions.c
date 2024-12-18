/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:06:41 by amasiuk           #+#    #+#             */
/*   Updated: 2024/12/18 14:01:05 by amasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	transist(t_lex_state *current_state, char ch_read)
{
	if ((*current_state == L_QUOTE && ch_read == '\'')
		|| (*current_state == L_DQUOTE && ch_read == '"')
		|| (*current_state == L_INIT && !ft_strchr("<' |\">", ch_read)))
	{
		*current_state = L_STRING;
	}
	else if (ch_read == '\'')
	{
		if (*current_state == L_STRING)
			*current_state = L_QUOTE;
		else
			*current_state = L_STRING;
	}
	else if (ch_read == '"')
	{
		if (*current_state == L_STRING)
			*current_state = L_DQUOTE;
		else
			*current_state = L_STRING;
	}
	else if (*current_state == L_STRING && ft_strchr("< |>", ch_read))
	{
		*current_state = L_INIT;
	}
}

void	append_lexer_token(t_list **tokens, char *cmd)
{
	t_token_data	*last_token;
	char			*read;
	char			*new_value;

	if (!tokens || !*tokens || !cmd)
		return ;
	last_token = ft_lstlast(*tokens)->content;
	read = ft_substr(cmd, 0, 1);
	if (!read)
		return ;
	new_value = ft_strjoin(last_token->value, read);
	free(read);
	if (!new_value)
		return ;
	free(last_token->value);
	last_token->value = new_value;
}

t_list	*new_lexer_token(t_token token_type, char *value)
{
	t_token_data	*new;

	new = ft_calloc(1, sizeof(t_token_data));
	if (!new)
		return (NULL);
	new->token = token_type;
	new->name = ft_strdup("");
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	if (value)
		new->value = value;
	else
	{
		new->value = ft_strdup("");
		if (!new->value)
		{
			free(new->name);
			free(new);
			return (NULL);
		}
	}
	return (ft_lstnew(new));
}

void	free_lexer_token_data(void *token)
{
	t_token_data	*tmp;

	if (!token)
		return ;
	tmp = (t_token_data *)token;
	if (!tmp)
		return ;
	if (tmp->value)
		free(tmp->value);
	if (tmp->name)
		free(tmp->name);
	free(tmp);
}
