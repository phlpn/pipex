/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:57:39 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/25 13:44:50 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

// malloc, free and exit
# include <stdlib.h>

// open, close, read, write, access, dup2, execve, fork and pipe
# include <unistd.h>

// wait, waitpid
# include <sys/wait.h>

// constants related to file control and manipulation
# include <fcntl.h>

// macros for increased readability
# define TRUE 0
# define CHILD 0
# define ERROR -1

// enum used when calling the open_file function
typedef enum e_flow
{
	WRITE,
	READ
}	t_flow;

void	exit_mgmt(char *msg, int exit_code);
char	*getcmdp(char *cmd, char **envp);
void	ft_free_split(char **split);

#endif