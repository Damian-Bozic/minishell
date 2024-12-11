/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:53:28 by dbozic            #+#    #+#             */
/*   Updated: 2024/09/24 15:53:29 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_echo(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!argv)
		return (db_error("ft_echo recieved NULL input", 0));
	if (!argv[0])
		return (db_error("ft_echo recieved bad input", 0));
	if (argv[1] && ft_strcmp("-n", argv[1]) == 0)
	{
		flag = 1;
		i++;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		i++;
	}
	return (1);
}

// static void	space_between_args(int *flag)
// {
// 	if (*flag == 1)
// 	{
// 		ft_putchar_fd(' ', 1);
// 		*flag = 2;
// 	}
// 	if (*flag == 0)
// 		*flag = 2;
// }

// static void	print_env(char *arg, int env_len, char **envp, int *flag)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(arg, envp[i], env_len) == 0)
// 		{
// 			if (envp[i][env_len] == '=')
// 			{
// 				while (envp[i][env_len])
// 				{
// 					space_between_args(flag);
// 					ft_putchar_fd(envp[i][env_len + 1], 1);
// 					env_len++;
// 				}
// 			}
// 		}
// 		i++;
// 	}
// }

// static void	print_with_args(char *arg, char **envp)
// {
// 	int			i;
// 	static int	flag = 0;
// 	int			env_len;

// 	i = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i] == '$')
// 		{
// 			env_len = 0;
// 			while ((arg[i + env_len + 1]) && arg[i + env_len + 1] != '$'
// 				&& arg[i + env_len + 1] != '=')
// 				env_len++;
// 			print_env(&arg[i + 1], env_len, envp, &flag);
// 			i += env_len;
// 		}
// 		else
// 		{
// 			space_between_args(&flag);
// 			ft_putchar_fd(arg[i], 1);
// 		}
// 		i++;
// 	}
// 	if (flag == 2)
// 		flag = 1;
// }

// int	ft_echo(char **argv, char **envp)
// {
// 	int	i;
// 	int	j;
// 	int	flag;

// 	i = 1;
// 	j = 0;
// 	flag = 0;
// 	if (!argv || !argv[0])
// 		return (db_error("ft_echo recieved NULL argv", 0));
// 	if (argv[1] && ft_strcmp("-n", argv[1]) == 0)
// 	{
// 		flag = 1;
// 		i = 2;
// 	}
// 	while (argv[i])
// 	{
// 		print_with_args(argv[i], envp);
// 		i++;
// 	}
// 	if (!flag)
// 		ft_printf("\n");
// 	return (1);
// }
