/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:57:45 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/29 11:33:21 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file, int read)
{
	int	fd;

	if (read)
		fd = open(file, O_RDONLY, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd == ERROR)
		exit_mgmt("Error: open failed\n", EXIT_FAILURE);
	return (fd);
}

void	close_fds_execmd(int openfd, int *fd, char **cmd, char **envp)
{
	if (close(openfd) == ERROR)
		exit_mgmt("Error: close failed\n", EXIT_FAILURE);
	if (close(fd[0]) == ERROR)
		exit_mgmt("Error: close failed\n", EXIT_FAILURE);
	if (close(fd[1]) == ERROR)
		exit_mgmt("Error: close failed\n", EXIT_FAILURE);
	if (execve(getcmdp(cmd[0], envp), cmd, envp) == ERROR)
		exit_mgmt("Error: execve failed\n", EXIT_FAILURE);
}

void	left_process(int *fd, char **cmd, char **envp, char *file)
{
	int	fd_in;

	if (!cmd)
		exit_mgmt("Error: split failed\n", EXIT_FAILURE);
	fd_in = open_file(file, READ);
	if (dup2(fd_in, STDIN_FILENO) == ERROR)
		exit_mgmt("Error: dup2 failed\n", EXIT_FAILURE);
	if (dup2(fd[1], STDOUT_FILENO) == ERROR)
		exit_mgmt("Error: dup2 failed\n", EXIT_FAILURE);
	close_fds_execmd(fd_in, fd, cmd, envp);
}

void	right_process(int *fd, char **cmd, char **envp, char *file)
{
	int	fd_out;

	if (!cmd)
		exit_mgmt("Error: split failed\n", EXIT_FAILURE);
	fd_out = open_file(file, WRITE);
	if (dup2(fd[0], STDIN_FILENO) == ERROR)
		exit_mgmt("Error: dup2 failed\n", EXIT_FAILURE);
	if (dup2(fd_out, STDOUT_FILENO) == ERROR)
		exit_mgmt("Error: dup2 failed\n", EXIT_FAILURE);
	close_fds_execmd(fd_out, fd, cmd, envp);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	left;
	pid_t	right;

	if (ac != 5)
		exit_mgmt("./pipex infile cmd1 cmd2 outfile\n", 1);
	if (pipe(fd) == ERROR)
		exit_mgmt("Error: pipe failed\n", EXIT_FAILURE);
	left = fork();
	if (left == ERROR)
		exit_mgmt("Error: fork failed\n", EXIT_FAILURE);
	if (left == CHILD)
		left_process(fd, ft_split(av[2], ' '), envp, av[1]);
	right = fork();
	if (right == ERROR)
		exit_mgmt("Error: fork failed\n", EXIT_FAILURE);
	if (right == CHILD)
		right_process(fd, ft_split(av[3], ' '), envp, av[4]);
	waitpid(left, NULL, 0);
	waitpid(right, NULL, 0);
	exit_mgmt(NULL, EXIT_SUCCESS);
}
