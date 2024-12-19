/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:05:43 by amasiuk           #+#    #+#             */
/*   Updated: 2024/12/19 13:16:30 by amasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command_node(void *command_list_node)
{
	t_command	*cmd;
	int			i;

	if (!command_list_node)
		return ;
	cmd = (t_command *)command_list_node;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free(cmd);
}

void	free_command_list(t_list **command_list)
{
	if (!command_list || !*command_list)
		return ;
	ft_lstclear(command_list, free_command_node);
}
