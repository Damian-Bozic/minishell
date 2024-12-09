/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:26:54 by amasiuk           #+#    #+#             */
/*   Updated: 2024/12/05 16:47:46 by amasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_g_state		g_status;

void	close_shell(t_data *data)
{
	//big function to free all data stuffs
	ft_printf("close_shell closing shell\n");
	free(data);
	exit(1);
}

static t_list	*get_command_list(char *input_line, t_data *data)
{
	t_list	*tokens_list;
	t_list	*commands_list;

	ft_printf("get command list start\n");
	if (!input_line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		close_shell(data);
	}
	// expand_variables(); something to get our ex.variables
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
	data->envs = init_envs(env, NULL, NULL, NULL);
	if (!data->envs)
	{
		free(data);
		return (NULL);
	}
	data->stdin_dup = dup(STDIN_FILENO);
	data->stdout_dup = dup(STDOUT_FILENO);
	return (data);
}

// int	main(void)
// {
// 	int i;

// 	i = 0;
// 	while (i < 10)
// 	{
// 		printf("+\n");
// 		i++;
// 		if (i == 5)
// 			continue;
// 		printf("%d\n", i);
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*input;

	(void)argc;
	(void)argv;
	ft_printf("Minishell start\n");
	data = init_data(envp);
	if (!data)
		return (255); //can be also 0, no pronlem
	while (42)
	{
		ft_printf("main while loop complete\n");
		set_interactive_signals();
		input = readline("MiniShell% > ");
		ft_printf("taken input from readline:\n%s\n", input);
		add_history(input);
		ft_printf("added input to history\n");
		set_non_interactive_signals();
		data->command_list = get_command_list(input, data);
		if (!data->command_list)
			continue ;

		ft_printf("Valid command list found\n");
		// translate

		// execute

		/* if (ft_lstsize(data->command_list) == 1)
			g_status.status_code = execute_input(data, data->command_list);
		else if (ft_lstsize(data->command_list) > 1)
			g_status.status_code = execute_with_pipe(data);
        
        this is how i'm seing that, but it's okay to change it
            */
		free_command_list(&(data->command_list));
	}
	return (EXIT_SUCCESS);
}






int test(const char *s)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	return (i);
}

// int main(void)
// {
// 	char str = "hello";
// 	int i;

// 	i = 0;

// 	ft_print("str = %d\n", test("hello"));
// 	return (1);
// }
