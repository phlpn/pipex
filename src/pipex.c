/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:57:45 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/23 17:02:05 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int *fd, char **cmd, char **envp, char *file)
{
	int	fd_in;

	fd_in = open_file(file, INPUT);
	if (dup2(fd_in, STDIN_FILENO) == ERROR)
		exit_mgmt("Error: dup2 failed\n", EXIT_FAILURE);
	if (dup2(fd[1], STDOUT_FILENO) == ERROR)
		exit_mgmt("Error: dup2 failed\n", EXIT_FAILURE);
	if (close(fd[0]) == ERROR)
		exit_mgmt("Error: close failed\n", EXIT_FAILURE);
	if (close(fd[1]) == ERROR)
		exit_mgmt("Error: close failed\n", EXIT_FAILURE);
	execve(getcmdp(cmd[0], envp), cmd, envp);
	exit_mgmt("Error: execve failed\n", EXIT_FAILURE);
}

void	parent_process(int *fd, char **cmd, char **envp, char *file)
{
	int	fd_out;

	fd_out = open_file(file, OUTPUT);
	if (dup2(fd[0], STDIN_FILENO) == ERROR)
		exit_mgmt("Error: dup2 failed\n", EXIT_FAILURE);
	if (dup2(fd_out, STDOUT_FILENO) == ERROR)
		exit_mgmt("Error: dup2 failed\n", EXIT_FAILURE);
	if (close(fd[0]) == ERROR)
		exit_mgmt("Error: close failed\n", EXIT_FAILURE);
	if (close(fd[1]) == ERROR)
		exit_mgmt("Error: close failed\n", EXIT_FAILURE);
	execve(getcmdp(cmd[0], envp), cmd, envp);
	exit_mgmt("Error: execve failed\n", EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	int		pid;
	char	**cmd1;
	char	**cmd2;

	if (ac != 5)
		exit_mgmt("./pipex file1 cmd1 cmd2 file2\n", 1);
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	if (!cmd1 || !cmd2)
		exit_mgmt("Error: malloc failed\n", EXIT_FAILURE);
	if (pipe(fd) == ERROR)
		exit_mgmt("Error: pipe failed\n", EXIT_FAILURE);
	pid = fork();
	if (pid == ERROR)
		exit_mgmt("Error: fork failed\n", EXIT_FAILURE);
	if (pid == CHILD)
		child_process(fd, cmd1, envp, av[1]);
	else
	{
		wait(NULL);
		parent_process(fd, cmd2, envp, av[4]);
	}
	return (ft_free_split(cmd1), ft_free_split(cmd2),
		exit_mgmt(NULL, EXIT_SUCCESS), EXIT_SUCCESS);
}
