/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doc_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:51:41 by dbozic            #+#    #+#             */
/*   Updated: 2024/10/29 12:58:46 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*read_doc2(int fd, char *buffer, char *rtn)
{
	int	i;

	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, 127);
		if (i == -1)
		{
			free(buffer);
			free(rtn);
			return (db_nerror("read fail in read_doc"));
		}
		if (i == 0)
			break ;
		buffer[i] = '\0';
		rtn = ft_strjoin_mod(rtn, buffer, ft_strlen(rtn), ft_strlen(buffer));
		if (!rtn)
		{
			free(buffer);
			return (db_nerror("malloc fail in read_doc"));
		}
	}
	free (buffer);
	buffer = NULL;
	return (rtn);
}

// read_doc will attempt to open the file given in *filename, then attempt to,
//  read it, and return the contents.
// on failure read_doc returns NULL.
char	*read_doc(char	*filename)
{
	char	*buffer;
	char	*rtn;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (db_nerror("read_doc failed to open a file descriptor"));
	buffer = malloc(128);
	if (!buffer)
		return (db_nerror("malloc fail in read_doc"));
	ft_bzero(buffer, 128);
	rtn = ft_strdup("");
	if (!rtn)
	{
		free(buffer);
		return (db_nerror("malloc fail in read_doc"));
	}
	buffer = read_doc2(fd, buffer, rtn);
	fd = close(fd);
	if (fd == -1)
	{
		free(buffer);
		return (db_nerror("read_doc failed to open a file descriptor"));
	}
	return (buffer);
}

// write_doc takes in *filename and *content and will try to make or overwrite,
//  the file named in *filename, and fill it with *content.
// write_doc returns 1 on success and 0 on error, and it prints its own error.
int	write_doc(char *filename, char *content)
{
	int	fd;

	if (!filename || !content)
		return (db_error("write_doc recieved a NULL input", 0));
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (db_error("write_doc failed to open a file descriptor", 0));
	write(fd, content, ft_strlen(content));
	fd = close(fd);
	if (fd == -1)
		return (db_error("write_doc failed to close a file descriptor", 0));
	return (1);
}

// append_doc takes in *filename and *content and will try to append to,
//  the file named in *filename, if the file doesnt exist, it is created,
//  and filled with *contents.
// append_doc returns 1 on success and 0 on error, and it prints its own error.
int	append_doc(char *filename, char *content)
{
	int		fd;
	char	*orig;

	if (!filename || !content)
		return (db_error("append_doc recieved a NULL input", 0));
	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (db_error("append_doc failed to open a file descriptor", 0));
	orig = read_doc(filename);
	if (!orig)
		return (db_error("read_doc failed in append_doc", 0));
	orig = ft_strjoin_mod(orig, content, ft_strlen(orig), ft_strlen(content));
	if (!orig)
	{
		fd = close(fd);
		if (fd == -1)
			return (db_error("append_doc failed to close a fd", 0));
		return (0);
	}
	write(fd, orig, ft_strlen(orig));
	free(orig);
	fd = close(fd);
	if (fd == -1)
		return (db_error("append_doc failed to close a file descriptor", 0));
	return (1);
}
