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
	char	*buffer;

	// ft_printf("get command list start\n");
	if (!input_line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		close_shell(data);
	}
	// ft_printf("input line: %s\n", input_line);
	buffer = replace_envs(input_line, convert_envs_to_envp(data->envs));
	// ft_printf("buffer line: %s\n", buffer);
	if (!buffer)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		close_shell(data);		
	}
	// expand_variables(); something to get our ex.variables
	if (data->env)
		free(data->env);
	data->env = convert_envs_to_envp(data->envs);
	if (!data->env)
	{
		//free everything and close
		db_nerror("data->env failed to allocated");
	}
	tokens_list = lexer_analysis(buffer);
	free(input_line);
	free(buffer);
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

static char	**init_exec_dir(t_data *data, char *input)
{
	int		i;
	char	**rtn;
	char	*temp;

	i = 0;
	temp = ft_getenv("PATH", data->env);
	if (!temp)
		return (db_nerror("init_exec_dir failed to find $PATH var"));
	rtn = ft_split(temp, ':');
	if (!rtn)
		return (db_nerror("malloc fail in exec_without_pipes"));
	while (rtn[i])
	{
		temp = ft_strjoin(rtn[i], "/");
		if (!temp)
			return (db_nerror("malloc fail in exec_without_pipes"));
		free(rtn[i]);
		rtn[i] = temp;
		temp = ft_strjoin(rtn[i], input);
		if (!temp)
			return (db_nerror("malloc fail in exec_without_pipes"));
		free(rtn[i]);
		rtn[i] = temp;
		i++;
	}
	return (rtn);
}

int	exec_without_pipes2(t_data *data, t_command *cmd)
{
	int		pid;
	int		i;
	char	**dir;

	i = 0;
	dir = init_exec_dir(data, cmd->args[0]);
	if (!dir)
	{
		return (0);
	}
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		while (dir[i] && execve(dir[i], cmd->args, data->env) == -1)
			i++;
		ft_putstr_fd(cmd->args[0], 2);
		write(2, ": command not found\n", 21);
		free_ptr_array(dir);
		//free *data here
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (1);
}

int	exec_without_pipes(t_data *data)
{
	t_command *cmd;


	if (!data || !data->command_list || !data->command_list->content)
		return (db_error("exec_without_pipes recieved NULL data", 0));
	cmd = data->command_list->content;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (db_error("exec_without_pipes recieved NULL input", 0));
	printf("fd in = %d and ft out = %d\n", cmd->in_fileno, cmd->out_fileno);
	// dup2(cmd->in_fileno, STDIN_FILENO);
	// dup2(STDOUT_FILENO, cmd->out_fileno);
	if (ft_strcmp("echo", cmd->args[0]) == 0)
		ft_echo(cmd->args);
	else if (ft_strcmp("cd", cmd->args[0]) == 0)
		ft_cd(cmd->args, data->env); // make sure data->env and data->envs is synced
	else if (ft_strcmp("env", cmd->args[0]) == 0)
		ft_env(data->envs);
	else if (ft_strcmp("export", cmd->args[0]) == 0)
		ft_export(cmd->args, data->envs);
	else if (ft_strcmp ("pwd", cmd->args[0]) == 0)
		ft_pwd();
	else if (ft_strcmp("unset", cmd->args[0]) == 0)
		ft_unset(cmd->args, data->envs);
	return (exec_without_pipes2(data, cmd));
}

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
		// ft_printf("main while loop complete\n");
		set_interactive_signals();
		input = readline("MiniShell% > ");
		// ft_printf("taken input from readline:\n%s\n", input);
		add_history(input);
		// ft_printf("added input to history\n");
		set_non_interactive_signals();
		data->command_list = get_command_list(input, data);
		if (!data->command_list)
			continue ;

		// ft_printf("Valid command list found\n\n");
		// translate

		int	i = 0;
		t_list *cur;
		t_command *command;	
		cur = data->command_list;
		while (cur)
		{
			// printf("START OF NODE\n");
			command = (t_command *)cur->content;
			i = 0;
			// pipex(command->args, convert_envs_to_envp(data->envs), data->envs);
			while (command->args[i])
			{
				// printf("%s\n", command->args[i]);
				i++;
			}

			// printf("END OF NODE\n");
			cur = cur->next;
		}

		// executesadas
		exec_without_pipes(data);
		/* if (ft_lstsize(data->command_list) == 1)
			g_status.status_code = execute_input(data, data->command_list);
		else if (ft_lstsize(data->command_list) > 1)
			g_status.status_code = execute_with_pipe(data);
        
        this is how i'm seing that, but it's okay to change it
            */
		// ft_printf("\n");
		free_command_list(&(data->command_list));
	}
	return (EXIT_SUCCESS);
}






// int	main(int argc, char **argv, char **envp)
// {
// 	printf("%d, %s, %s\n", argc, argv[0], envp[0]);

// 	t_envs *envs;
// 	envs = init_envs(envp, NULL, NULL, NULL);
// 	if (!envs)
// 		return (0);

// 	// ft_unset("PATH", envs);
// 	char	**input;

// 	input = (char **)ft_calloc(128, sizeof(char *));
// 	input[0] = ft_strdup("echo");
// 	input[1] = ft_strdup("$HOME");
// 	input[2] = ft_strdup("'PIPE");
// 	input[3] = ft_strdup("cat");
// 	// input[1] = ft_strdup("'PIPE");
// 	// input[2] = ft_strdup("wc");
// 	// input[3] = ft_strdup("-l");
// 	input[4] = NULL; //ft_strdup("-l"); //NULL;
// 	input[5] = NULL;
// 	// input[5] = ft_strdup("'PIPE");
// 	// input[6] = ft_strdup("wc");
// 	// input[7] = ft_strdup("-c");
// 	input[8] = NULL;

// 	pipex(input, convert_envs_to_envp(envs), envs);
// 	free_envs(envs);
// }