/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnixProcesses.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:07:50 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/11 17:32:55 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY

#include <stdio.h> // printf()
#include <unistd.h> // fork()

// The fork() function

// int	main(void)
// {
// 	int	id = fork(); // fork() returns an int: -1 for error, 0 for child process and process ID of child process to the parent process
// 	// if (id)
// 	// 	fork();
// 	// printf("Hello World from id: %i!\n", id);
// 	if (id == 0)
// 		printf("Hello from child process [%i]\n", id);
// 	else
// 		printf("Hello from main process [%i]\n", id);
// 	return (0);
// }

// Waiting for processes to finish (using the wait function)

#include <stdlib.h> // wait()

// int	main(void)
// {
// 	int	id = fork();
// 	int	n;
// 	if (id == 0)
// 		n = 1;
// 	else
// 		n = 6;
// 	if (id != 0)
// 		wait(NULL);
// 	int i = n;
// 	while (i < n + 5){
// 		printf("%d ", i++);
// 		fflush(stdout);
// 	}
// 	if (id)
// 		printf("\n");
// 	return (0);
// }

// Process Ids

// #include "sys/wait.h" // getpid(), getppid()

// int	main(void)
// {
// 	int	id = fork();
// 	if (id == 0)
// 		sleep(1);
// 	printf("Current ID: %i, Parent ID: %i\n",
// 		getpid(), getppid());
// 	int res = wait(NULL);
// 	if (res == -1)
// 		printf("No childen to wait for.\n");
// 	else
// 		printf("Process %i finished execution.\n", res);
// 	return (0);
// }

// Calling fork() multiple times

#include <errno.h>

// int	main(void)
// {
// 	int	id1 = fork();
// 	int	id2 = fork();
// 	int	i = 0;
// 	if (id1 == 0)
// 	{
// 		if (id2 == 0)
// 			printf("We are process Y.\n");
// 		else
// 			printf("We are process X.\n");
// 	}
// 	else
// 	{
// 		if (id2 == 0)
// 			printf("We are process Z.\n");
// 		else
// 			printf("We are the parent process.\n");
// 	}
// 	while(wait(NULL) != -1 || errno != ECHILD)
// 		printf("Waited for a child to finish\n");
// 	return (0);
// }

// Comunicating between processes using pipes

int	main(void)
{
	int fd[2];
	// fd[0] - read
	// fd[1] - write
	if (pipe(fd) == -1)
		return (printf("An error occured with opening the pipe\n"), -1);
	int id = fork();
	if (id == 0)
	{
		close(fd[0]);
		int	x;
		printf("Input a number: ");
		scanf("%i", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
			return (printf("An error occured with writing to the pipe\n"), -1);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int	y;
		if (read(fd[0], &y, sizeof(int)) == -1)
			return (printf("An error occured with reading from the pipe\n"), -1);
		close(fd[0]);
		printf("Got from child process: %i\n", y);
		wait(NULL);
	}
	return (0);
}
