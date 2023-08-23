/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:57:39 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/23 17:24:15 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

// malloc, free and exit
# include <stdlib.h>

// open, close, read, write, access, dup2, execve, fork and pipe
# include <unistd.h>

// wait
# include <sys/wait.h>

// constants related to file control and manipulation
# include <fcntl.h>

// macros for increased readability
# define TRUE 0
# define CHILD 0
# define ERROR -1

// simple enum used with open_file to specify flow
typedef enum e_flow
{
	INPUT,
	OUTPUT
}	t_flow;

void	exit_mgmt(char *msg, int exit_code);
int		open_file(char *file, t_flow flow);
void	ft_free_split(char **split);
char	*getenvp(char **envp);
char	*getcmdp(char *cmd, char **envp);

#endif