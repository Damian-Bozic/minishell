/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envs_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:45:41 by dbozic            #+#    #+#             */
/*   Updated: 2024/10/23 14:02:43 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_functions.h"

t_envs	*find_in_env_list(char *name, t_envs *envs)
{
	t_envs	*current;

	current = envs;
	while (current)
	{
		if (!ft_strcmp(current->name, name))
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	free_envs(t_envs *envs)
{
	t_envs	*current;
	t_envs	*next;

	if (!envs)
		return (db_error("free_envs recieved NULL input", 0));
	current = envs;
	while (current->next)
	{
		next = current->next;
		if (current->contents)
			free(current->contents);
		if (current->name)
			free(current->name);
		free(current);
		current = next;
	}
	if (current->name)
		free(current->name);
	if (current->contents)
		free(current->contents);
	free(current);
	return (1);
}

// might break if there is no '=' in the starting envps
static t_envs	*new_env2(t_envs *new, char *contents, char *env_full)
{
	int		i;
	char	*var_name;

	i = 0;
	while (env_full[i] && env_full[i] != '=')
		i++;
	if (!env_full[i])
	{
		free(new);
		free(contents);
		return (db_nerror("new_env2 recieved invalid input"));
	}
	var_name = malloc(i + 1);
	if (!var_name)
	{
		free(new);
		free(contents);
		return (db_nerror("new_env2 malloc fail"));
	}
	ft_strlcpy(var_name, env_full, i + 1);
	var_name[i] = 0;
	new->name = var_name;
	new->contents = contents;
	new->next = NULL;
	return (new);
}

static t_envs	*new_env(char *env_full)
{
	t_envs	*new;
	char	*contents;

	if (!env_full)
		return (db_nerror("new_env2 recieved NULL input"));
	new = malloc(sizeof(t_envs));
	if (!new)
		return (NULL);
	contents = ft_strdup (ft_strchr(env_full, '=') + 1);
	if (!contents)
	{
		free(new);
		return (db_nerror("new_env2 malloc fail"));
	}
	return (new_env2(new, contents, env_full));
}

t_envs	*init_envs(char **envp, t_envs *head, t_envs *current, t_envs *last)
{
	static int	i = 0;

	if (!envp || head || current || last || i != 0)
		return (db_nerror("init_evns recieved a bad input"));
	while (envp[i])
	{
		current = new_env(envp[i]);
		if (!current)
		{
			free_envs(head);
			return (NULL);
		}
		if (!head)
		{
			head = current;
			last = head;
		}
		else
		{
			last->next = current;
			last = last->next;
		}
		i++;
	}
	return (head);
}

// static t_envs *new_env(char *env_full)
// {
// 	t_envs	*new;
// 	char	*var_name;
// 	char	*contents;
// 	int		i;

// 	i = 0;
// 	if (!env_full)
// 		return(db_nerror("new_env2 recieved NULL input"));
// 	new = malloc(sizeof(t_envs));
// 	if (!new)
// 		return (NULL);
// 	contents = ft_strdup(ft_strchr(env_full, '=') + 1);
// 	if (!contents)
// 	{
// 		free(new);
// 		return(db_nerror("new_env2 malloc fail"));
// 	}
// 	while (env_full[i] && env_full[i] != '=')
// 		i++;
// 	if (!env_full[i])
// 	{
// 		free(new);
// 		free(contents);
// 		return(db_nerror("new_env2 recieved invalid input"));
// 	}
// 	var_name = malloc(i + 1);
// 	if (!var_name)
// 	{
// 		free(new);
// 		free(contents);
// 		return(db_nerror("new_env2 malloc fail"));
// 	}
// 	ft_strlcpy(var_name, env_full, i + 1);
// 	var_name[i] = 0;
// 	new->name = var_name;
// 	new->contents = contents;
// 	new->next = NULL;
// 	return (new);
// }