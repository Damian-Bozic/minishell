/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_actions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:08:25 by dbozic            #+#    #+#             */
/*   Updated: 2024/12/18 15:08:26 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_error	ac2(t_command *cmd)
{
	free(cmd->args);
	free(cmd);
	return (MALLOC);
}

t_error	append_command(t_list **cmd_list, char *new_cmd)
{
	t_command	*cmd;

	if (!cmd_list)
		return (MALLOC);
	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (MALLOC);
	cmd->args = ft_calloc(2, sizeof(char *));
	if (!cmd->args)
	{
		free(cmd);
		return (MALLOC);
	}
	if (new_cmd)
	{
		cmd->args[0] = ft_strdup(new_cmd);
		if (!cmd->args[0])
			return (ac2(cmd));
		cmd->ac = 1;
	}
	ft_lstadd_back(cmd_list, ft_lstnew(cmd));
	return (NO_ERROR);
}
