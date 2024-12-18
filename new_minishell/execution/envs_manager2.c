/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_manager2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:08:12 by dbozic            #+#    #+#             */
/*   Updated: 2024/12/18 15:08:13 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_env(char ***env, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while ((*env)[i] && i < size)
	{
		new_env[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	free(*env);
	return (new_env);
}

static int	add_to_env2(char ***env, int *idx, char *new_entry)
{
	if (*idx != -1 && (*env)[*idx])
	{
		free((*env)[*idx]);
		(*env)[*idx] = new_entry;
	}
	else
	{
		*idx = calc_env_size(*env);
		*env = realloc_env(env, *idx + 1);
		if (!(*env))
		{
			free(new_entry);
			return (12);
		}
		(*env)[*idx] = new_entry;
	}
	return (1);
}

int	add_to_env(char ***env, char *key, char *value)
{
	int		idx;
	char	*eq_value;
	char	*new_entry;

	idx = get_env_index(*env, key);
	if (!value)
		value = "";
	eq_value = ft_strjoin("=", value);
	if (!eq_value)
		return (12);
	new_entry = ft_strjoin(key, eq_value);
	if (!new_entry)
	{
		free(eq_value);
		return (12);
	}
	if (add_to_env2(env, &idx, new_entry) == 12)
		return (12);
	free(eq_value);
	return (0);
}
