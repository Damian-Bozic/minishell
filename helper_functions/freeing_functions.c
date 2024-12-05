/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:07:15 by dbozic            #+#    #+#             */
/*   Updated: 2024/12/05 14:07:16 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_ptr_ptr_array(char ***array)
{
	int	i;
	int	j;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			free(array[i][j]);
			j++;
		}
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_ptr_array(char **ptr_array)
{
	int	i;

	i = 0;
	if (!ptr_array)
		return ;
	while (ptr_array[i])
	{
		free(ptr_array[i]);
		i++;
	}
	free(ptr_array);
	ptr_array = NULL;
}

char	**db_dup_arr_of_str(char **array)
{
	int		i;
	int		n;
	char	**rtn;

	i = 0;
	n = 0;
	if (!array)
		return (NULL);
	while (array[n])
		n++;
	rtn = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!rtn)
		return (NULL);
	while (i < n)
	{
		rtn[i] = ft_strdup(array[i]);
		if (!rtn[i])
		{
			free_ptr_array(rtn);
			return (NULL);
		}
		i++;
	}
	return (rtn);
}
