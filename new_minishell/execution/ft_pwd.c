/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:22:04 by dbozic            #+#    #+#             */
/*   Updated: 2024/12/16 01:42:12 by amasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(void)
{
	char	*cwd;
	int		code_number;

	code_number = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		code_number = 1;
		return (code_number);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (code_number);
}
