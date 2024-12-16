/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:53:28 by dbozic            #+#    #+#             */
/*   Updated: 2024/12/16 03:12:24 by amasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_if_n_flag(char *flag)
{
	int	i;

	if (ft_strncmp(flag, "-n", 2) != 0)
		return (false);
	i = 1;
	while (flag[i] && flag[i] == 'n')
		i++;
	return (!flag[i]);
}

static void	print_echo_string(char **args, int idx)
{
	while (args[idx])
	{
		ft_putstr_fd(args[idx], STDOUT_FILENO);
		if (args[idx + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		idx++;
	}
}

int	echo_builtin(t_command *cmd)
{
	if (cmd->ac == 2 && check_if_n_flag(cmd->args[1]))
		return (0);
	if (cmd->ac == 1)
		ft_putendl_fd("", STDOUT_FILENO);
	else if (cmd->ac >= 2 && !check_if_n_flag(cmd->args[1]))
	{
		print_echo_string(cmd->args, 1);
		ft_putendl_fd("", STDOUT_FILENO);
	}
	else
		print_echo_string(cmd->args, 2);
	return (0);
}
