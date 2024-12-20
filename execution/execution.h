/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:53:55 by dbozic            #+#    #+#             */
/*   Updated: 2024/11/26 20:09:26 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <limits.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# ifndef PATH_MAX
#  define PATH_MAX 8192
# endif



typedef struct s_pipex
{
	char	**input;
	char	**envp;
	char	***flags;
	char	***dir;
	int		(*fd)[2];
	int		*pid;
	int		n_of_cmds;
}		t_pipex;

int		ft_pwd(void);
int		ft_echo(char **argv);
int		ft_cd(char **argv, char **envp);

t_envs	*init_envs(char **envp, t_envs *head, t_envs *current, t_envs *last);
int		free_envs(t_envs *envs);
t_envs	*find_in_env_list(char *name, t_envs *envs);
int		ft_export(char **argv, t_envs *envs);
int		ft_unset(char **argv, t_envs *envs);
int		ft_env(t_envs *envs);
char	**convert_envs_to_envp(t_envs *envs);

int		pipex(char **input, char **envp, t_envs *envs);
void	close_all_pipes(t_pipex *pipex);
void	free_pipex(t_pipex *pipex);
int		init_pipex_dir_and_flags(t_pipex *pipex, int i, int k);
int		assign_pipex(t_pipex *pipex, char **argv, char **envp);
int		exec_pipex(t_pipex *pipex, t_envs *envs);

char	*read_doc(char *filename);
int		write_doc(char *filename, char *content);
int		append_doc(char *filename, char *content);

char	*ft_getenv(char *env_name, char **envp);
char	*replace_envs(char *arg, char **envp);
char	*ft_strjoin_mod(char *alstr, char *str, size_t s1_n, size_t s2_n);

#endif
