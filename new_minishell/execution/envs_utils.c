/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:10:37 by amasiuk           #+#    #+#             */
/*   Updated: 2024/12/16 03:25:24 by amasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_environments(t_data *data)
{
	free_env_copy(data->env, calc_env_size(data->env));
	free_env_copy(data->export_env, calc_env_size(data->export_env));
	free(data->env);
	free(data->export_env);
}

void	free_env_copy(char **env, int last_index)
{
	int	i;

	i = -1;
	while (++i < last_index)
		free(env[i]);
}

size_t	calc_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**copy_env(char **env)
{
	int		i;
	char	**env_copy;

	i = 0;
	env_copy = ft_calloc(calc_env_size(env) + 1, sizeof(char *));
	if (!env_copy)
		return (NULL);
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]);
		if (!(env_copy[i]))
			return (free_env_copy(env_copy, i), NULL);
		i++;
	}
	return (env_copy);
}
