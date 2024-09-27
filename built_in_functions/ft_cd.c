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

#include "built_in_functions.h"

static int	check_cd_format(char *input)
{
	return (1);

	printf("%s\n", input);
	// if (valid is valid)
	// 	return (1);
	// printf("Invalid input\n");
	// return (0);
}

static int	cd_absolute(char *input)
{
	if(check_cd_format(input) == 0)
		return (2);
	if (chdir(input) == -1)
	{
		printf("invalid change directory\n");
		return (2);
	}
	return (1);
}

static int	cd_relative(char *input, char *cwd)
{
	if(check_cd_format(input) == 0)
		return (2);
	printf("cd relative is not working yet%s\n", cwd);
	return (1);
}

int	ft_cd(char *input)
{
	char	*cwd;

	if (!input)
		return(db_error("ft_cd recieved a NULL input", 0));
	if (input[0] == '/')
		return (cd_absolute(input));
	cwd = malloc(PATH_MAX);
	if (!cwd)
		return (db_error("Malloc fail in ft_cd", 0));
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		if (cd_relative(input, cwd) == 0)
		{
			free(cwd);
			return (0);
		}
		free(cwd);
		return (1);
	}
	free(cwd);
	return (db_error("ft_cd failed to getcwd", 0));
}
