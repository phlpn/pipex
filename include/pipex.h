/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:57:39 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/08 14:36:23 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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


// LABS
void	dup2_demo(void);
void	access_demo(void);
void	execve_demo(void);
void	fork_demo(void);
void	pipe_demo(void);
void	unlink_demo(void);

#endif