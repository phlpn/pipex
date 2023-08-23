/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:57:39 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/23 12:21:05 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

// perror
# include <stdio.h>

// malloc, free and exit
# include <stdlib.h>

// open, close, read, write, access, unlink, dup, dup2, execve, fork and pipe
# include <unistd.h>

// strerror
# include <string.h>

// pid_t
# include <sys/types.h>

// waitpid and wait
# include <sys/wait.h>

// structures and constants related to file status and permission bits
# include <sys/stat.h>

// constants related to file control and manipulation
# include <fcntl.h>

// error codes and related information
# include <errno.h>

# define CHILD 0
# define TRUE 0
# define ERROR -1

typedef enum e_flow
{
	IN,
	OUT
}	t_flow;

void	exit_mgmt(char *msg, int exit_code);
int		open_file(char *file, t_flow flow);
void	ft_free_split(char **split);
char	*getcmdp(char *cmd, char **envp);

#endif