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
}

int pipex(void)
{
    int fd[2];
    int pid1;
    int pid2;
    char    **flags;

    flags = (char **)ft_calloc(3, sizeof(char *));
    flags[0] = ft_strdup("ls");
    flags[1] = ft_strdup("-l");

    if (pipe(fd) == -1)
        return (db_error("pipex failed to create pipe", 0));

    pid1 = fork();
    if (pid1 < 0)
        return (db_error("pipex failed to create fork", 0));
    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO); // will make stdout point toward fd[1];
        close(fd[0]);
        close(fd[1]);
        if (execve("/bin/ls", flags, NULL) == -1)
        {
            free_ptr_array(flags);
            return (db_error("execve error", 0));
        }
    }

    pid2 = fork(); 
    if (pid2 < 0)
        return (db_error("pipex failed to create fork", 0));
    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO); // will make stdin point toward fd[0];
        close(fd[0]);
        close(fd[1]);
        flags[0] = "wc";
        if (execve("/bin/wc", flags, NULL) == -1)
        {
            free_ptr_array(flags);
            return (db_error("execve error", 0));
        }
    }
    free_ptr_array(flags);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (1);
}

int	main(int argc, char **argv, char **envp)
{
	printf("%d, %s, %s\n", argc, argv[0], envp[0]);

	pipex();


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