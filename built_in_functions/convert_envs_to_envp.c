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

#include "built_in_functions.h"

static char	*ft_strjoin_mod(char *alstr, char *str, size_t s1_n, size_t s2_n)
{
	size_t		i;
	size_t		j;
	char		*rtn;

	i = 0;
	j = 0;
	rtn = malloc(s1_n + s2_n + 1);
	if (!rtn)
		free(alstr);
	if (!rtn)
		return (NULL);
	while (i < s1_n)
	{
		rtn[i] = alstr[i];
		i++;
	}
	while (j < s2_n)
	{
		rtn[i + j] = str[j];
		j++;
	}
	rtn[i + j] = '\0';
	free(alstr);
	alstr = NULL;
	return (rtn);
}

static void free_ptr_array(char **ptr_array)
{
    int i;

    i = 0;
    if (!ptr_array)
        return ;
    while (ptr_array[i])
    {
        free(ptr_array[i]);
        i++;
    }
    free(ptr_array);
}

static char **convert_envs2(char **rtn, t_envs *current, int i)
{
	while(current)
	{
		rtn[i] = ft_strdup(current->name);
		if (!rtn[i])
		{
			free_ptr_array(rtn);
			return(db_nerror("malloc fail in convert_envs"));
		}
		rtn[i] = ft_strjoin_mod(rtn[i], "=", ft_strlen(rtn[i]), 1);
		if (!rtn[i])
		{
			free_ptr_array(rtn);
			return(db_nerror("malloc fail in convert_envs"));
		}
		rtn[i] = ft_strjoin_mod(rtn[i], current->contents,
				ft_strlen(rtn[i]), ft_strlen(current->contents));
		if (!rtn[i])
		{
			free_ptr_array(rtn);
			return(db_nerror("malloc fail in convert_envs"));
		}
		i++;
		current = current->next;
	}
	return (rtn);
}

char **convert_envs_to_envp(t_envs *envs)
{
	int		i;
	char	**rtn;
	t_envs	*current;

	i = 0;
	current = envs;
	if (!current)
		return(db_nerror("convert_envs recieved NULL input"));
	while (current)
	{
		current = current->next;
		i++;
	}
	ft_printf("calloc requesting %i of size %i\n", i, sizeof(char *));
	rtn = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!rtn)
		return(db_nerror("malloc fail in convert_envs"));
	return (convert_envs2(rtn, envs, 0));
}
