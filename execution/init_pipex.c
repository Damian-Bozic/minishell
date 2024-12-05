/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:11:56 by dbozic            #+#    #+#             */
/*   Updated: 2024/12/05 14:11:57 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	count_commands(char **input, int i)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	while (input[j])
	{
		if (ft_strcmp("'PIPE", input[j]) == 0)
		{
			if (flag == 0)
				return (db_error("pipex syntax error", 0));
			flag = 0;
		}
		else
		{
			if (flag == 0)
				i++;
			flag = 1;
		}
		j++;
	}
	if (flag == 0)
		return (db_error("pipex syntax error", 0));
	return (i);
}

int	assign_pipex(t_pipex *pipex, char **argv, char **envp)
{
	if (!pipex)
	{
		free_ptr_array(argv);
		free_ptr_array(envp);
		return (db_error("malloc fail in pipex", 0));
	}
	pipex->input = argv;
	pipex->envp = envp;
	pipex->n_of_cmds = count_commands(argv, 0);
	pipex->flags = (char ***)ft_calloc(pipex->n_of_cmds + 1, sizeof(char **));
	pipex->dir = (char ***)ft_calloc(pipex->n_of_cmds + 1, sizeof(char **));
	pipex->pid = ft_calloc(pipex->n_of_cmds + 1, sizeof(int));
	pipex->fd = ft_calloc(pipex->n_of_cmds + 1, sizeof(int [2]));
	if (!pipex->flags || !pipex->dir || !pipex->pid || !pipex->fd)
	{
		free_pipex(pipex);
		return (db_error("malloc fail in pipex", 0));
	}
	if (!init_pipex_dir_and_flags(pipex, 0, 0))
	{
		free_pipex(pipex);
		return (0);
	}
	return (1);
}

static int	init_pipex_dir(t_pipex *pipex, char *input, int k)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_getenv("PATH", pipex->envp);
	if (!temp)
		return (db_error("init_pipex_dir failed to find $PATH var", 0));
	pipex->dir[k] = ft_split(temp, ':');
	if (!pipex->dir[k])
		return (db_error("malloc fail in pipex", 0));
	while (pipex->dir[k][i])
	{
		temp = ft_strjoin(pipex->dir[k][i], "/");
		if (!temp)
			return (db_error("malloc fail in pipex", 0));
		free(pipex->dir[k][i]);
		pipex->dir[k][i] = temp;
		temp = ft_strjoin(pipex->dir[k][i], input);
		if (!temp)
			return (db_error("malloc fail in pipex", 0));
		free(pipex->dir[k][i]);
		pipex->dir[k][i] = temp;
		i++;
	}
	return (1);
}

static int	count_args(char **input)
{
	int	i;

	i = 0;
	while (input[i] && ft_strcmp("'PIPE", input[i]) != 0)
	{
		i++;
	}
	return (i);
}

int	init_pipex_dir_and_flags(t_pipex *pipex, int i, int k)
{
	int	j;

	if (pipex->n_of_cmds == 0)
		return (0);
	while (pipex->input[i])
	{
		if (!init_pipex_dir(pipex, pipex->input[i], k))
			return (0);
		pipex->flags[k] = (char **)ft_calloc(count_args(&pipex->input[i]) + 1,
				sizeof(char *));
		if (!pipex->flags[k])
			return (db_error("malloc fail in pipex", 0));
		j = 0;
		while (pipex->input[i + j]
			&& ft_strcmp("'PIPE", pipex->input[i + j]) != 0)
		{
			pipex->flags[k][j] = ft_strdup(pipex->input[i + j]);
			if (!pipex->flags[k][j])
				return (db_error("malloc fail in pipex", 0));
			j++;
		}
		i = i + j + 1;
		k++;
	}
	return (1);
}
