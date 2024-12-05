/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:06:17 by dbozic            #+#    #+#             */
/*   Updated: 2024/12/05 16:06:18 by dbozic           ###   ########.fr       */
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