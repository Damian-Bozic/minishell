/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:26:54 by amasiuk           #+#    #+#             */
/*   Updated: 2024/12/16 03:36:29 by amasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_g_state		g_status;

static t_list	*get_command_list(char *input_line, t_data *data)
{
	t_list	*tokens_list;
	t_list	*commands_list;

	if (!input_line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		close_shell(data, g_status.status_code);
	}
	expand_variables(&input_line, data, false);
	tokens_list = lexer_analysis(input_line);
	free(input_line);
	if (!tokens_list)
		return (NULL);
	commands_list = parser_analysis(tokens_list, data);
	ft_lstclear(&tokens_list, &free_lexer_token_data);
	return (commands_list);
}

static t_data	*init_data(char **env)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = copy_env(env);
	if (!(data->env))
		return (free(data), NULL);
	data->export_env = copy_env(env);
	if (!(data->export_env))
		return (free(data->env), free(data), NULL);
	data->stdin_dup = dup(STDIN_FILENO);
	data->stdout_dup = dup(STDOUT_FILENO);
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*input;

	(void)argc;
	(void)argv;
	data = init_data(envp);
	if (!data)
		return (255);
	while (1)
	{
		set_interactive_signals();
		input = readline("ZabkaTeamMiniShell% > ");
		if (!input)
		{
			break ;
		}
		add_history(input);
		set_non_interactive_signals();
		data->command_list = get_command_list(input, data);
		if (!data->command_list)
		{
			free(input);
			continue ;
		}
		if (ft_lstsize(data->command_list) == 1)
			g_status.status_code = execute_input(data, data->command_list);
		else if (ft_lstsize(data->command_list) > 1)
			g_status.status_code = execute_with_pipe(data);
		free_command_list(&(data->command_list));
		free(input);
	}
	return (0);
}
