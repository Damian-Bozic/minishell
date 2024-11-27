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
#include <termios.h>
#include "signal.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

static void free_ptr_ptr_array(char ***array)
{
    int i;
	int	j;

    i = 0;
    if (!array)
        return ;
    while (array[i])
    {
		j = 0;
		while(array[i][j])
		{
			free(array[i][j]);
			j++;
		}
        free(array[i]);
        i++;
    }
    free(array);
	array = NULL;
}

static void free_ptr_array(char **ptr_array)
{
    int i;

    i = 0;
    if (!ptr_array)
        return ;
    while (ptr_array[i])
    {
        free(ptr_array[i]);
        i++;
    }
    free(ptr_array);
	ptr_array = NULL;
}


char **db_dup_arr_of_str(char **array)
{
	int		i;
	int		n;
	char	**rtn;

	i = 0;
	n = 0;
	if (!array)
		return (NULL);
	while (array[n])
		n++;
	rtn = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!rtn)
		return (NULL);
	while (i < n)
	{
		rtn[i] = ft_strdup(array[i]);
		if (!rtn[i])
		{
			free_ptr_array(rtn);
			return (NULL);
		}
		i++;
	}
	return (rtn);
}

// /!\ INPUTS /!\
//
// Commands
//  any system commands like ls should be input the same as their /bin
//   name, for example, the diectory for wc is /bin/wc, therefore its
//	 input should be "wc". 
//  pipex does not check for whether the command is valid, therefore an
//   invalid input will end in an execve error.
//
// Flags and Arguments
//  after a command you can add infinite flags, they must be valid, or
//   else you will recieve an invalid option error.
//  an example of valid flags for the ls command would be:
//   "-l" "-a"
//   "-l"
//   "-la"
//  inbuilt commands such as "echo" are executed on a case by case basis
//   for example, echo will take in flags only at the first argument
//   invalid flags, such as -l, will not be treated as a flag, and instead
//   as an argument, and will be printed.
//  use for in built echo would look something like this
//   "echo"
//   "-n"    <-- flag first
//   "hello"
//   "world"
//  use of export or unset in a pipe would do nothing.
//  use of cd wouldnt work, its errors wouldnt be sent through a pipe.
//
// Pipes
//	between each command there should be a pipe, otherwise pipex will
//   close without executing and will print an error.
//  pipes are recognised with the token "'PIPE"
//
// a complete input for pipex would look something like:
//  "ls"		CMD
//  "-la"		ARG
//  "'PIPE"		PIPE
//  "wc"		CMD
//  "-l"		ARG
//  "'PIPE"		PIPE
//  "echo"		CMD
//  "cheese"	ARG
//  NULL		END
//
// /!\ HANDLING /!\
//
// pipex will return 0 upon error, and 1 upon success, and will print
//  its own error.
// pipex will free both char **input and char **envp.
//

int count_commands(char **input)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (input[j])
	{
		if (ft_strcmp("'PIPE", input[j]) == 0)
		{
			if (flag == 0)
				return (db_error("pipex syntax error", 0));
			flag = 0;
		}
		else
		{
			if (flag == 0)
				i++;
			flag = 1;
		}
		j++;
	}
	if (flag == 0)
		return (db_error("pipex syntax error", 0));
	return (i);
}

int	count_args(char **input)
{
	int	i;

	i = 0;
	while (input[i] && ft_strcmp("'PIPE", input[i]) != 0)
	{
		i++;
	}
	return (i);
}

// int	init_pipex_dir_and_flags(char **input, char ***flags, char ***dir, int n)
// {
// 	int	i;
// 	int	j;
// 	int	k;

// 	i = 0;
// 	k = 0;
// 	if (n == 0)
// 		return (0);
// 	while (input[i])
// 	{
// 		dir[k] = ft_strjoin("/cheese/", input[i]);
// 		if (!dir[k])
// 			return (db_error("malloc fail in pipex", 0));
// 		flags[k] = (char **)ft_calloc(count_args(&input[i]) + 1, sizeof(char *));
// 		if (!flags[k])
// 			return (db_error("malloc fail in pipex", 0));
// 		j = 0;
// 		while (input[i + j] && ft_strcmp("'PIPE", input[i + j]) != 0)
// 		{
// 			flags[k][j] = ft_strdup(input[i + j]);
// 			if (!flags[k][j])
// 				return (db_error("malloc fail in pipex", 0));
// 			j++;
// 		}
// 		i = i + j + 1;
// 		k++;
// 	}
// 	return (1);
// }

typedef struct s_pipex
{
	char	**input;
	char	**envp;
	char	***flags;
	char	***dir;
    int		(*fd)[2];
	int		*pid;
	int		n_of_cmds;
}		t_pipex;

int	init_pipex_dir(t_pipex *pipex, char *input, int k)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_getenv("PATH", pipex->envp);
	if (!temp)
		return (db_error("init_pipex_dir failed to find $PATH var", 0));
	pipex->dir[k] = ft_split(temp, ':');
	if (!pipex->dir[k])
		return (db_error("malloc fail in pipex", 0));
	while(pipex->dir[k][i])
	{
		temp = ft_strjoin(pipex->dir[k][i], "/");
		if (!temp)
			return (db_error("malloc fail in pipex", 0));
		free(pipex->dir[k][i]);
		pipex->dir[k][i] = temp;
		temp = ft_strjoin(pipex->dir[k][i], input);
		if (!temp)
			return (db_error("malloc fail in pipex", 0));
		free(pipex->dir[k][i]);
		pipex->dir[k][i] = temp;
		i++;
	}
	return (1);
}

int	init_pipex_dir_and_flags(t_pipex *pipex)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	if (pipex->n_of_cmds == 0)
		return (0);
	while (pipex->input[i])
	{
		if (!init_pipex_dir(pipex, pipex->input[i], k))
			return (0);
		pipex->flags[k] = (char **)ft_calloc(count_args(&pipex->input[i]) + 1, 
				sizeof(char *));
		if (!pipex->flags[k])
			return (db_error("malloc fail in pipex", 0));
		j = 0;
		while (pipex->input[i + j] && ft_strcmp("'PIPE", pipex->input[i + j]) != 0)
		{
			pipex->flags[k][j] = ft_strdup(pipex->input[i + j]);
			if (!pipex->flags[k][j])
				return (db_error("malloc fail in pipex", 0));
			j++;
		}
		i = i + j + 1;
		k++;
	}
	return (1);
}

void free_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->input)
		free_ptr_array(pipex->input);
	if (pipex->envp)
		free_ptr_array(pipex->envp);
	if (pipex->flags)
		free_ptr_ptr_array(pipex->flags);
	if (pipex->dir)
		free_ptr_ptr_array(pipex->dir);
	if (pipex->fd)
		free(pipex->fd);
	if (pipex->pid)
		free(pipex->pid);
	free(pipex);
}

void close_all_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	// printf("closed pipes called\n");
	while (i < pipex->n_of_cmds)
	{
		// ft_printf("closed a pipe\n");
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		i++;
	}
}

void close_all_unused_pipes(t_pipex *pipex, int pipe_out, int pipe_in)
{
	int	i;

	i = 0;
	while (i < pipex->n_of_cmds)
	{
		if (i != pipe_in)
			close(pipex->fd[i][0]);
		if (i != pipe_out)
			close(pipex->fd[i][1]);
		i++;
	}
}

void exec_addon(t_pipex *pipex, int cmd_no)
{
	char	**flags;
	char	**envp;
	char	**dir;
	int		i;

	i = 0;
	flags = db_dup_arr_of_str(pipex->flags[cmd_no]);
	envp = db_dup_arr_of_str(pipex->envp);
	dir = db_dup_arr_of_str(pipex->dir[cmd_no]);
	free_pipex(pipex);
	if (!flags || !dir || !envp)
	{
		db_nerror("malloc fail in pipex");
		free_ptr_array(flags);
		free_ptr_array(envp);
		free_ptr_array(dir);
		return ;
	}
	while (dir[i] && execve(dir[i], flags, envp) == -1)
		i++;
	write(2, flags[0], sizeof(flags[0]));
	write(2, ": command not found\n", 21);
	free_ptr_array(flags);
	free_ptr_array(envp);
	free_ptr_array(dir);
}

	// else if (ft_strcmp(dir, "/bin/export"))
	// 	ft_export(var_name, contents, envs);
	// else if (ft_strcmp(dir, "/bin/unset"))
	// 	ft_unset(argv[1], envs);

int	exec_builtin(char **argv, char **envp, t_envs *envs)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argv, envp);
	else if (ft_strcmp(argv[0], "cd") == 0)
		ft_cd(argv, envp);
	else if (ft_strcmp(argv[0], "env") == 0)
		ft_env(envs);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd();
	else
		return (0);
	return (1);
}

int pipex(char **input, char **envp, t_envs *envs)
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
	{
		free_ptr_array(input);
		free_ptr_array(envp);
		return (db_error("malloc fail in pipex", 0));
	}
	pipex->input = input;
	pipex->envp = envp;
	pipex->n_of_cmds = count_commands(input);
	pipex->flags = (char ***)ft_calloc(pipex->n_of_cmds + 1, sizeof(char **));
	pipex->dir = (char ***)ft_calloc(pipex->n_of_cmds + 1, sizeof(char **));
	pipex->pid = ft_calloc(pipex->n_of_cmds + 1, sizeof(int));
	pipex->fd = ft_calloc(pipex->n_of_cmds + 1, sizeof(int[2]));
	if (!pipex->flags || !pipex->dir || !pipex->pid || !pipex->fd)
	{
		free_pipex(pipex);
		return (db_error("malloc fail in pipex", 0));
	}
	if (!init_pipex_dir_and_flags(pipex))
	{
		free_pipex(pipex);
		return (0);
	}

	// make sure to check for errors and free below here is not checked!
	while (i < pipex->n_of_cmds - 1)
	{
		// printf("made pipe %d\n", i);
		if (pipe(pipex->fd[i]) == -1)
			return (db_error("pipex failed to create a pipe", 0));
		i++;
	}
	i = 0;
	// ft_printf("amount of cmds %d\n", pipex->n_of_cmds);
	while (i < pipex->n_of_cmds)
	{
		// ft_printf("making fork %d\n", i);
		pipex->pid[i] = fork();
		if (pipex->pid[i] < 0)
		{
			close_all_pipes(pipex);
			free_pipex(pipex);
			return (db_error("pipex failed to create fork", 0));
		}
		if (pipex->pid[i] == 0)
		{
			close_all_unused_pipes(pipex, i, i - 1);
			if (i != pipex->n_of_cmds - 1)
			{
				dup2(pipex->fd[i][1], STDOUT_FILENO);
				close(pipex->fd[i][1]);
			}
			if (i != 0)
			{
				dup2(pipex->fd[i - 1][0], STDIN_FILENO);
				close(pipex->fd[i - 1][0]);
			}
			if (exec_builtin(pipex->flags[i], pipex->envp, envs))
			{
				free_pipex(pipex);
				return (1);
			}
			else
				exec_addon(pipex, i);
			return (0);
		}
		i++;
	}
	// ft_printf("closing main pipes\n");
	close_all_pipes(pipex);
	i = 0;
	while (i < pipex->n_of_cmds)
	{
		waitpid(pipex->pid[i], NULL, 0);
		// ft_printf("main found pid %d finished\n", i);
		i++;
	}
	free_pipex(pipex);
    return (1);
}


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
	input[0] = ft_strdup("ejarsd");
	// input[1] = NULL; // ft_strdup("$HOME/minishell");
	// input[2] = NULL; // ft_strdup("'PIPE");
	// input[3] = ft_strdup("cd");
	input[1] = ft_strdup("'PIPE");
	input[2] = ft_strdup("export");
	input[3] = ft_strdup("HELO=world");
	input[4] = NULL;
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
