/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:22:04 by dbozic            #+#    #+#             */
/*   Updated: 2024/09/25 16:22:23 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_functions.h"

// This can only tell its current directory, probably wont work in practice

int	ft_pwd(void)
{
	char	*cwd;

	cwd = malloc(PATH_MAX);
	if (!cwd)
		return (db_error("Malloc fail in ft_pwd", 0));
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (1);
	}
	free(cwd);
	return (db_error("ft_pwd failed to getcwd", 0));
}

// int	main(void)
// {
// 	ft_pwd();
// }