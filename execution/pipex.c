/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:04:55 by dbozic            #+#    #+#             */
/*   Updated: 2024/12/05 14:04:57 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// /!\ INPUTS /!\
//
// Commands
//  any system commands like ls should be input the same as their /bin
//   name, for example, the diectory for wc is /bin/wc, therefore its
//	 input should be "wc". 
//  pipex does not check for whether the command is valid, therefore an
//   invalid input will end in an execve error.
//
// Flags and Arguments
//  after a command you can add infinite flags, they must be valid, or
//   else you will recieve an invalid option error.
//  an example of valid flags for the ls command would be:
//   "-l" "-a"
//   "-l"
//   "-la"
//  inbuilt commands such as "echo" are executed on a case by case basis
//   for example, echo will take in flags only at the first argument
//   invalid flags, such as -l, will not be treated as a flag, and instead
//   as an argument, and will be printed.
//  use for in built echo would look something like this
//   "echo"
//   "-n"    <-- flag first
//   "hello"
//   "world"
//  use of export or unset in a pipe would do nothing.
//  use of cd wouldnt work, its errors wouldnt be sent through a pipe.
//
// Pipes
//	between each command there should be a pipe
//  pipes are recognised with the token "'PIPE"
//  commands are recognised as the first argument in argv and any
//   argument after a pipe.
//
// a complete input for pipex would look something like:
//  "ls"		CMD
//  "-la"		ARG
//  "'PIPE"		PIPE
//  "wc"		CMD
//  "-l"		ARG
//  "'PIPE"		PIPE
//  "echo"		CMD
//  "cheese"	ARG
//  NULL		END
//
// /!\ HANDLING /!\
//
// pipex will return 0 upon error, and 1 upon success, and will print
//  its own error.
// pipex will free both char **input and char **envp.
//

void	free_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->input)
		free_ptr_array(pipex->input);
	if (pipex->envp)
		free_ptr_array(pipex->envp);
	if (pipex->flags)
		free_ptr_ptr_array(pipex->flags);
	if (pipex->dir)
		free_ptr_ptr_array(pipex->dir);
	if (pipex->fd)
		free(pipex->fd);
	if (pipex->pid)
		free(pipex->pid);
	free(pipex);
}

void	close_all_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n_of_cmds)
	{
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		i++;
	}
}

int	check_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n_of_cmds - 1)
	{
		if (pipe(pipex->fd[i]) == -1)
		{
			close_all_pipes(pipex);
			free_pipex(pipex);
			return (db_error("pipex failed to create a pipe", 0));
		}
		i++;
	}
	return (1);
}

int	pipex(char **input, char **envp, t_envs *envs)
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = malloc(sizeof(t_pipex));
	if (!assign_pipex(pipex, input, envp))
		return (0);
	if (!check_pipes(pipex))
		return (0);
	if (!exec_pipex(pipex, envs))
		return (0);
	close_all_pipes(pipex);
	i = 0;
	while (i < pipex->n_of_cmds)
	{
		waitpid(pipex->pid[i], NULL, 0);
		i++;
	}
	free_pipex(pipex);
	return (1);
}
