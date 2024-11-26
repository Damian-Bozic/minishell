/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:12:52 by dbozic            #+#    #+#             */
/*   Updated: 2024/09/27 17:13:05 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// returns 0 on error
// returns 1 on success
// returns 2 on invalid directory change

char	*ft_getenv(char *env_name, char **envp)
{
	int		i;
	char	*rtn;

	i = 0;
	rtn = NULL;
	if (!envp)
		return (db_nerror("ft_getenv recieved NULL envp"));
	if (!env_name)
		return (db_nerror("ft_getenv recieved NULL input"));
	while (envp[i])
	{
		if (ft_strncmp(env_name, envp[i], ft_strlen(env_name)) == 0)
		{
			rtn = &envp[i][ft_strlen(env_name) + 1];
			break ;
		}
		i++;
	}
	return (rtn);
}

int	ft_cd(char **argv, char **envp)
{
	char	*dir;

	dir = NULL;
	if (!argv)
		return (db_error("ft_cd recieved a NULL argv", 0));
	if (argv[0] && argv[1] && argv[2])
		return (db_error("ft_cd recieved too many arguments", 0));
	if (!argv[1])
	{
		if (chdir(ft_getenv("HOME", envp)) == -1)
			return (db_error("ft_cd failed to find a $HOME directory", 0));
		return (1);
	}
	dir = filter_argv(argv[1], envp);
	if (!dir)
		return (db_error("malloc fail in ft_cd", 0));
	if (chdir(dir) == -1)
	{
		ft_printf("no such file or directory: %s\n", dir);
		free(dir);
		return (0);
	}
	free(dir);
	return (1);
}

// returns 0 on error
// returns 1 on success
// returns 2 on invalid directory change

// int	ft_cd(char *input)
// {
// 	char	*dir;

// 	if (!input)
// 		return (db_error("ft_cd recieved a NULL input", 0));
// 	if (!input[0])
// 	{
// 		dir = getenv("HOME");
// 		if (!dir)
// 			return (db_error("No HOME environmental variable found", 0));
// 		if (chdir(dir) == -1)
// 		{
// 			ft_printf("No such file or directory\n");
// 			return (2);
// 		}
// 	}
// 	else if (chdir(input) == -1)
// 	{
// 		ft_printf("No such file or directory\n");
// 		return (2);
// 	}
// 	return (1);
// }

// Before I found out chdir can do relative commands for me VVV

// static int	exec_relative_move(int i, int j, char *cwd, char *input)
// {
// 	char	*dir;

// 	if (ft_strlen(&input[i]) > 3 && ft_strncmp(&input[i], "../", 3))
// 	{
// 		dir = ft_strdup(cwd);
// 		if (!dir)
// 			return (db_error("Malloc fail in ft_cd.c", 0));
// 		i = ft_strlen(dir);
// 		while (dir[i] != '/')
// 		{
// 			dir[i] = 0;
// 			i--;
// 		}
// 	}
// 	else
// 	{
// 		dir = malloc(ft_strlen(cwd) + (j - i));
// 		if (!dir)
// 			return (db_error("Malloc fail in ft_cd.c", 0));
// 		ft_strlcpy(dir, cwd, ft_strlen(cwd));
// 		ft_strlcpy(&dir[ft_strlen(dir)], &input[i], i - j);
// 	}
// 	ft_printf("%s\n", dir);
// 	if (chdir(dir) == -1)
// 	{
// 		printf("invalid change directory\n");
// 		return (2);
// 	}
// 	printf("valid change directory\n");
// 	return (1);
// }

// static int	cd_relative(char *input, char *cwd)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (check_cd_format(input) == 0)
// 		return (2);
// 	printf("cd relative is not complete yet%s\n", cwd);
// 	while (input[i])
// 	{
// 		if (input[i] != '/')
// 			i++;
// 		else
// 		{
// 			if (getcwd(cwd, PATH_MAX) != NULL)
// 			{
// 				exec_relative_move(i, j, cwd, input);
// 				j = i;
// 			}
// 			else
// 				return (db_error("ft_cd failed to getcwd", 0));
// 		}
// 	}
// 	return (1);
// }

// static int	cd_absolute(char *input)
// {
// 	if (check_cd_format(input) == 0)
// 		return (2);
// 	if (chdir(input) == -1)
// 	{
// 		printf("invalid change directory\n");
// 		return (2);
// 	}
// 	return (1);
// }

// static int	cd_relative(char *input, char *cwd)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (check_cd_format(input) == 0)
// 		return (2);
// 	printf("cd relative is not complete yet%s\n", cwd);
// 	while (input[i])
// 	{
// 		if (input[i] != '/')
// 			i++;
// 		else
// 		{
// 			if (getcwd(cwd, PATH_MAX) != NULL)
// 			{
// 				exec_relative_move(i, j, cwd, input);
// 				j = i;
// 			}
// 			else
// 				return (db_error("ft_cd failed to getcwd", 0));
// 		}
// 	}
// 	return (1);
// }

// int	ft_cd(char *input)
// {
// 	char	*cwd;

// 	if (!input)
// 		return(db_error("ft_cd recieved a NULL input", 0));
// 	if (input[0] == '/')
// 		return (cd_absolute(input));
// 	cwd = malloc(PATH_MAX);
// 	if (!cwd)
// 		return (db_error("Malloc fail in ft_cd.c", 0));
// 	if (getcwd(cwd, PATH_MAX) != NULL)
// 	{
// 		if (cd_relative(input, cwd) == 0)
// 		{
// 			free(cwd);
// 			return (0);
// 		}
// 		free(cwd);
// 		return (1);
// 	}
// 	free(cwd);
// 	return (db_error("ft_cd failed to getcwd", 0));
// }