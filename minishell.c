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

// int	main(int argc, char **argv, char **envp)
// {
// 	printf("%d, %s\n", argc, argv[0]);
// 	t_envs	*envs;

// 	envs = init_envs(envp, NULL, NULL, NULL);
// 	if (!envs)
// 		return (0);
// 	ft_env(envs);
// 	ft_export(ft_strdup("CHEESE"), ft_strdup("cheesewow"), envs);
// 	ft_export(ft_strdup("CHEESE"), ft_strdup("wow"), envs);
// 	ft_export(ft_strdup("CHEESESSSSS"), ft_strdup("wow"), envs);
// 	ft_env(envs);
// 	printf("\n\n\n");
// 	ft_unset("CHEESE", envs);
// 	ft_env(envs);
// 	printf("\n\n\n");
// 	ft_unset("CHEESE", envs);
// 	ft_unset("CHEESESSSS", envs);
// 	ft_env(envs);
// 	printf("\n\n\n");
// 	ft_export(ft_strdup(""), ft_strdup(""), envs);
// 	ft_env(envs);
// 	printf("\n\n\n");
// 	free_envs(envs);

// 	db_error("error check", 0);
// 	ft_pwd();
// 	ft_echo(1, "with -n flag");
// 	ft_echo(0, "without -n flag");
// 	ft_cd("Libft");
// 	ft_pwd();
// 	ft_cd("..");
// 	ft_pwd();
// 	ft_cd("/");
// 	ft_pwd();
// 	ft_cd("");
// 	ft_pwd();
// 	ft_cd("wow");
// 	ft_pwd();
// }