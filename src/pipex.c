/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:57:45 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/24 20:59:24 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file, t_flow flow)
{
	int	fd;

	if (flow == READ)
		fd = open(file, O_RDONLY, 0744);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd == ERROR)
		exit_mgmt("Error: open failed / file not found\n", EXIT_FAILURE);
	return (fd);
}

void	close_fd_execmd(int openfd, int *fd, char **cmd, char **envp)
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

void	child_process(int *fd, char **cmd, char **envp, char *file)
{
	int	fd_in;

	fd_in = open_file(file, READ);
	if (dup2(fd_in, STDIN_FILENO) == ERROR)
		exit_mgmt("Error: dup2 failed\n", EXIT_FAILURE);
	if (dup2(fd[1], STDOUT_FILENO) == ERROR)
		exit_mgmt("Error: dup2 failed\n", EXIT_FAILURE);
	close_fd_execmd(fd_in, fd, cmd, envp);
}

void	parent_process(int *fd, char **cmd, char **envp, char *file)
{
	int	fd_out;

	wait(NULL);
	fd_out = open_file(file, WRITE);
	if (dup2(fd[0], STDIN_FILENO) == ERROR)
		exit_mgmt("Error: dup2 failed\n", EXIT_FAILURE);
	if (dup2(fd_out, STDOUT_FILENO) == ERROR)
		exit_mgmt("Error: dup2 failed\n", EXIT_FAILURE);
	close_fd_execmd(fd_out, fd, cmd, envp);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
		exit_mgmt("./pipex file1 cmd1 cmd2 file2\n", 1);
	if (pipe(fd) == ERROR)
		exit_mgmt("Error: pipe failed\n", EXIT_FAILURE);
	pid = fork();
	if (pid == ERROR)
		exit_mgmt("Error: fork failed\n", EXIT_FAILURE);
	if (pid == CHILD)
		child_process(fd, ft_split(av[2], ' '), envp, av[1]);
	else
		parent_process(fd, ft_split(av[3], ' '), envp, av[4]);
	exit(EXIT_SUCCESS);
}
