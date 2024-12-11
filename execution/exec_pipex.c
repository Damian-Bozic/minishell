/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:14:29 by dbozic            #+#    #+#             */
/*   Updated: 2024/12/05 14:14:32 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	exec_addon(t_pipex *pipex, int cmd_no)
{
	char	**flags;
	char	**envp;
	char	**dir;
	int		i;

	i = 0;
	flags = db_dup_arr_of_str(pipex->flags[cmd_no]);
	envp = db_dup_arr_of_str(pipex->envp);
	dir = db_dup_arr_of_str(pipex->dir[cmd_no]);
	free_pipex(pipex);
	if (!flags || !dir || !envp)
	{
		db_nerror("malloc fail in pipex");
		free_ptr_array(flags);
		free_ptr_array(envp);
		free_ptr_array(dir);
		return ;
	}
	while (dir[i] && execve(dir[i], flags, envp) == -1)
		i++;
	write(2, flags[0], sizeof(flags[0]));
	write(2, ": command not found\n", 21);
	free_ptr_array(flags);
	free_ptr_array(envp);
	free_ptr_array(dir);
}

static int	exec_builtin(char **argv, char **envp, t_envs *envs)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		ft_cd(argv, envp);
	else if (ft_strcmp(argv[0], "env") == 0)
		ft_env(envs);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(argv[0], "export") == 0 || ft_strcmp(argv[0],
			"unset") == 0)
	{
		// check if these do anything
	}
	else
		return (0);
	return (1);
}

static void	close_all_unused_pipes(t_pipex *pipex, int pipe_out, int pipe_in)
{
	int	i;

	i = 0;
	while (i < pipex->n_of_cmds)
	{
		if (i != pipe_in)
			close(pipex->fd[i][0]);
		if (i != pipe_out)
			close(pipex->fd[i][1]);
		i++;
	}
}

static int	exec_pipex_handle_pipes(t_pipex *pipex, int i)
{
	close_all_unused_pipes(pipex, i, i - 1);
	if (i != pipex->n_of_cmds - 1)
	{
		if (dup2(pipex->fd[i][1], STDOUT_FILENO) == -1)
		{
			close_all_pipes(pipex);
			free_pipex(pipex);
			return (0);
		}
		close(pipex->fd[i][1]);
	}
	if (i != 0)
	{
		if (dup2(pipex->fd[i - 1][0], STDIN_FILENO) == -1)
		{
			close_all_pipes(pipex);
			free_pipex(pipex);
			return (0);
		}
		close(pipex->fd[i - 1][0]);
	}
	return (1);
}

int	exec_pipex(t_pipex *pipex, t_envs *envs)
{
	int	i;

	i = 0;
	while (i < pipex->n_of_cmds)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] < 0)
		{
			close_all_pipes(pipex);
			free_pipex(pipex);
			return (db_error("pipex failed to create fork", 0));
		}
		if (pipex->pid[i] == 0)
		{
			if (!exec_pipex_handle_pipes(pipex, i))
				return (0);
			if (exec_builtin(pipex->flags[i], pipex->envp, envs))
			{
				free_pipex(pipex);
				return (1);
			}
			else
				exec_addon(pipex, i);
			return (0);
		}
		i++;
	}
	return (1);
}
