/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_envs_to_envp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:45:11 by dbozic            #+#    #+#             */
/*   Updated: 2024/11/19 18:45:12 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	**convert_envs2(char **rtn, t_envs *current, int i)
{
	while (current)
	{
		rtn[i] = ft_strdup(current->name);
		if (!rtn[i])
		{
			free_ptr_array(rtn);
			return (db_nerror("malloc fail in convert_envs"));
		}
		rtn[i] = ft_strjoin_mod(rtn[i], "=", ft_strlen(rtn[i]), 1);
		if (!rtn[i])
		{
			free_ptr_array(rtn);
			return (db_nerror("malloc fail in convert_envs"));
		}
		rtn[i] = ft_strjoin_mod(rtn[i], current->contents,
				ft_strlen(rtn[i]), ft_strlen(current->contents));
		if (!rtn[i])
		{
			free_ptr_array(rtn);
			return (db_nerror("malloc fail in convert_envs"));
		}
		i++;
		current = current->next;
	}
	return (rtn);
}

char	**convert_envs_to_envp(t_envs *envs)
{
	int		i;
	char	**rtn;
	t_envs	*current;

	i = 0;
	current = envs;
	if (!current)
		return (db_nerror("convert_envs recieved NULL input"));
	while (current)
	{
		current = current->next;
		i++;
	}
	rtn = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!rtn)
		return (db_nerror("malloc fail in convert_envs"));
	return (convert_envs2(rtn, envs, 0));
}
