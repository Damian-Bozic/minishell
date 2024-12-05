/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:02:27 by dbozic            #+#    #+#             */
/*   Updated: 2024/09/19 15:02:39 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <termios.h>
// #include "signal.h"
// #include <sys/stat.h>
// #include <fcntl.h>


// $PATH /nfs/homes/dbozic/bin:/usr/local/sbin:/usr/local/bin:
//  /usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
int	main(int argc, char **argv, char **envp)
{
	printf("%d, %s, %s\n", argc, argv[0], envp[0]);

	t_envs *envs;
	envs = init_envs(envp, NULL, NULL, NULL);
	if (!envs)
		return (0);

	// ft_unset("PATH", envs);
	char	**input;

	input = (char **)ft_calloc(128, sizeof(char *));
	input[0] = ft_strdup("ls");
	input[1] = ft_strdup("-l");
	input[2] = ft_strdup("'PIPE");
	input[3] = ft_strdup("wc");
	// input[1] = ft_strdup("'PIPE");
	// input[2] = ft_strdup("wc");
	// input[3] = ft_strdup("-l");
	input[4] = NULL; //ft_strdup("-l"); //NULL;
	input[5] = NULL;
	// input[5] = ft_strdup("'PIPE");
	// input[6] = ft_strdup("wc");
	// input[7] = ft_strdup("-c");
	input[8] = NULL;

	pipex(input, convert_envs_to_envp(envs), envs);
	free_envs(envs);

	// char	*str;

	// str = read_doc("test.txt");

	// write_doc("test.txt", "much content\n");
	// str = read_doc("test.txt");
	// printf("%s\n", str);
	// free(str);

	// append_doc("test.txt", "appended stuffs\n");
	// str = read_doc("test.txt");
	// printf("%s\n", str);
	// free(str);

	// write_doc("test.txt", "overwritten contents\n");
	// str = read_doc("test.txt");
	// printf("%s\n", str);
	// free(str);

	// t_envs	*envs;
	// char	**envp2;
	// int		i = 0;

	// envs = init_envs(envp, NULL, NULL, NULL);
	// if (!envs)
	// 	return (0);

	// ft_export(ft_strdup("CHEESE"), ft_strdup("cheesewow"), envs);
	// ft_printf("start convert\n");
	// envp2 = convert_envs_to_envp(envs);
	// if (!envp2)
	// 	return(db_error("failed to envp2", 0));
	// while (envp2[i])
	// {
	// 	ft_printf("%s\n", envp2[i]);
	// 	i++;
	// }
	// free_ptr_array(envp2);
	// free_envs(envs);

	// ft_env(envs);
	// ft_export(ft_strdup("CHEESE"), ft_strdup("cheesewow"), envs);
	// ft_export(ft_strdup("CHEESE"), ft_strdup("wow"), envs);
	// ft_export(ft_strdup("CHEESESSSSS"), ft_strdup("wow"), envs);
	// ft_env(envs);
	// printf("\n\n\n");
	// ft_unset("CHEESE", envs);
	// ft_env(envs);
	// printf("\n\n\n");
	// ft_unset("CHEESE", envs);
	// ft_unset("CHEESESSSS", envs);
	// ft_env(envs);
	// printf("\n\n\n");
	// ft_export(ft_strdup(""), ft_strdup(""), envs);
	// ft_env(envs);
	// printf("\n\n\n");
	// free_envs(envs);

	// db_error("error check", 0);
	// ft_pwd();
	// ft_echo(1, "cat");
	// ft_echo(0, "meow");
	// ft_echo(1, "mewo");
	// ft_echo(0, "meew");
	// ft_echo(1, "wow");
	// ft_echo(0, "cheese");
	// ft_cd("Libft");
	// ft_pwd();
	// ft_cd("..");
	// ft_pwd();
	// ft_cd("/");
	// ft_pwd();
	// ft_cd("");
	// ft_pwd();
	// ft_cd("wow");
	// ft_pwd();
}

// int pipex(char **envp)
// {
//     int fd[2];
//     int pid1;
//     int pid2;
//     char    **flags;

// 	// no need to check for null envp since it could
// 	//  be input as empty.

//     flags = (char **)ft_calloc(3, sizeof(char *));
//     flags[0] = ft_strdup("cat");
//     flags[1] = ft_strdup("test.txt");

//     if (pipe(fd) == -1)
//         return (db_error("pipex failed to create pipe", 0));

//     pid1 = fork();
//     if (pid1 < 0)
// 	{
// 		close(fd[0]);
// 		close(fd[1]);
//         return (db_error("pipex failed to create fork", 0));
// 	}
// 	if (pid1 == 0)
//     {
//         // dup2(fd[1], STDOUT_FILENO); // will make stdout point toward fd[1];
//         close(fd[0]);
//         close(fd[1]);
// 		sleep(1);
//         if (execve("/bin/cat", flags, envp) == -1)
//         {
//             free_ptr_array(flags);
//             return (db_error("execve error", 0));
//         }
// 		return (1);
//     }

//     pid2 = fork(); 
//     if (pid2 < 0)
// 	{
// 		close(fd[0]);
// 		close(fd[1]);
//         return (db_error("pipex failed to create fork", 0));
// 	}
// 	if (pid2 == 0)
//     {
//         dup2(fd[0], STDIN_FILENO); // will make stdin point toward fd[0];
//         close(fd[0]);
//         close(fd[1]);
//         flags[0] = "wc";
// 		flags[1] = "-l";
//         if (execve("/bin/wc", flags, envp) == -1)
//         {
//             free_ptr_array(flags);
//             return (db_error("execve error", 0));
//         }
//     }
//     free_ptr_array(flags);
//     close(fd[0]);
//     close(fd[1]);
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);
// 	free_ptr_array(envp);
//     return (1);
// }


// int pipex(char **input, char **envp, t_envs *envs)
// {
// 	t_pipex	*pipex;
// 	int		i;

// 	i = 0;
// 	pipex = malloc(sizeof(t_pipex));
// 	if (!pipex)
// 	{
// 		free_ptr_array(input);
// 		free_ptr_array(envp);
// 		return (db_error("malloc fail in pipex", 0));
// 	}
// 	pipex->input = input;
// 	pipex->envp = envp;
// 	pipex->n_of_cmds = count_commands(input, 0);
// 	pipex->flags = (char ***)ft_calloc(pipex->n_of_cmds + 1, sizeof(char **));
// 	pipex->dir = (char ***)ft_calloc(pipex->n_of_cmds + 1, sizeof(char **));
// 	pipex->pid = ft_calloc(pipex->n_of_cmds + 1, sizeof(int));
// 	pipex->fd = ft_calloc(pipex->n_of_cmds + 1, sizeof(int[2]));
// 	if (!pipex->flags || !pipex->dir || !pipex->pid || !pipex->fd)
// 	{
// 		free_pipex(pipex);
// 		return (db_error("malloc fail in pipex", 0));
// 	}
// 	if (!init_pipex_dir_and_flags(pipex, 0, 0))
// 	{
// 		free_pipex(pipex);
// 		return (0);
// 	}

// 	// make sure to check for errors and free below here is not checked!
// 	while (i < pipex->n_of_cmds - 1)
// 	{
// 		// printf("made pipe %d\n", i);
// 		if (pipe(pipex->fd[i]) == -1)
// 		{
// 			close_all_pipes(pipex);
// 			free_pipex(pipex);
// 			return (db_error("pipex failed to create a pipe", 0));
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	// ft_printf("amount of cmds %d\n", pipex->n_of_cmds);
// 	while (i < pipex->n_of_cmds)
// 	{
// 		// ft_printf("making fork %d\n", i);
// 		pipex->pid[i] = fork();
// 		if (pipex->pid[i] < 0)
// 		{
// 			close_all_pipes(pipex);
// 			free_pipex(pipex);
// 			return (db_error("pipex failed to create fork", 0));
// 		}
// 		if (pipex->pid[i] == 0)
// 		{
// 			close_all_unused_pipes(pipex, i, i - 1);
// 			if (i != pipex->n_of_cmds - 1)
// 			{
// 				//check for write to file > >>
// 				dup2(pipex->fd[i][1], STDOUT_FILENO);
// 				close(pipex->fd[i][1]);
// 			}
// 			if (i != 0)
// 			{
// 				//check for read from file <
// 				// if (check_for_redirection(pipex, i))
// 				// {
// 				// 	//execute redirection
// 				// }
// 				dup2(pipex->fd[i - 1][0], STDIN_FILENO);
// 				close(pipex->fd[i - 1][0]);
// 			}
// 			if (exec_builtin(pipex->flags[i], pipex->envp, envs))
// 			{
// 				free_pipex(pipex);
// 				return (1);
// 			}
// 			else
// 				exec_addon(pipex, i);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	// ft_printf("closing main pipes\n");
// 	close_all_pipes(pipex);
// 	i = 0;
// 	while (i < pipex->n_of_cmds)
// 	{
// 		waitpid(pipex->pid[i], NULL, 0);
// 		// ft_printf("main found pid %d finished\n", i);
// 		i++;
// 	}
// 	free_pipex(pipex);
//     return (1);
// }

// int	assign_pipex(t_pipex *pipex, char **argv, char **envp)
// {
// 	if (!pipex)
// 	{
// 		free_ptr_array(argv);
// 		free_ptr_array(envp);
// 		return (db_error("malloc fail in pipex", 0));
// 	}
// 	pipex->input = argv;
// 	pipex->envp = envp;
// 	pipex->n_of_cmds = count_commands(argv, 0);
// 	pipex->flags = (char ***)ft_calloc(pipex->n_of_cmds + 1, sizeof(char **));
// 	pipex->dir = (char ***)ft_calloc(pipex->n_of_cmds + 1, sizeof(char **));
// 	pipex->pid = ft_calloc(pipex->n_of_cmds + 1, sizeof(int));
// 	pipex->fd = ft_calloc(pipex->n_of_cmds + 1, sizeof(int[2]));
// 	if (!pipex->flags || !pipex->dir || !pipex->pid || !pipex->fd)
// 	{
// 		free_pipex(pipex);
// 		return (db_error("malloc fail in pipex", 0));
// 	}
// 	if (!init_pipex_dir_and_flags(pipex, 0, 0))
// 	{
// 		free_pipex(pipex);
// 		return (0);
// 	}
// 	return (1);
// }

// int pipex(char **input, char **envp, t_envs *envs)
// {
// 	t_pipex	*pipex;
// 	int		i;

// 	i = 0;
// 	pipex = malloc(sizeof(t_pipex));
// 	if (!assign_pipex(pipex, input, envp))
// 		return (0);

// 	// make sure to check for errors and free below here is not checked!
// 	while (i < pipex->n_of_cmds - 1)
// 	{
// 		// printf("made pipe %d\n", i);
// 		if (pipe(pipex->fd[i]) == -1)
// 		{
// 			close_all_pipes(pipex);
// 			free_pipex(pipex);
// 			return (db_error("pipex failed to create a pipe", 0));
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	// ft_printf("amount of cmds %d\n", pipex->n_of_cmds);
// 	while (i < pipex->n_of_cmds)
// 	{
// 		// ft_printf("making fork %d\n", i);
// 		pipex->pid[i] = fork();
// 		if (pipex->pid[i] < 0)
// 		{
// 			close_all_pipes(pipex);
// 			free_pipex(pipex);
// 			return (db_error("pipex failed to create fork", 0));
// 		}
// 		if (pipex->pid[i] == 0)
// 		{
// 			close_all_unused_pipes(pipex, i, i - 1);
// 			if (i != pipex->n_of_cmds - 1)
// 			{
// 				//check for write to file > >>
// 				dup2(pipex->fd[i][1], STDOUT_FILENO);
// 				close(pipex->fd[i][1]);
// 			}
// 			if (i != 0)
// 			{
// 				//check for read from file <
// 				// if (check_for_redirection(pipex, i))
// 				// {
// 				// 	//execute redirection
// 				// }
// 				dup2(pipex->fd[i - 1][0], STDIN_FILENO);
// 				close(pipex->fd[i - 1][0]);
// 			}
// 			if (exec_builtin(pipex->flags[i], pipex->envp, envs))
// 			{
// 				free_pipex(pipex);
// 				return (1);
// 			}
// 			else
// 				exec_addon(pipex, i);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	// ft_printf("closing main pipes\n");
// 	close_all_pipes(pipex);
// 	i = 0;
// 	while (i < pipex->n_of_cmds)
// 	{
// 		waitpid(pipex->pid[i], NULL, 0);
// 		// ft_printf("main found pid %d finished\n", i);
// 		i++;
// 	}
// 	free_pipex(pipex);
//     return (1);
// }