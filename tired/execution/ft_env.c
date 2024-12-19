/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:53:28 by dbozic            #+#    #+#             */
/*   Updated: 2024/12/16 03:38:25 by amasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (cmd->ac > 1)
		return (db_error("env: too many arguments", 2));
	while ((data->env)[i])
	{
		ft_putendl_fd((data->env)[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
