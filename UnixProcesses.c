/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnixProcesses.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:07:50 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/15 16:35:27 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY

#include <stdio.h> // printf()
#include <unistd.h> // fork()

#define CHILD 0 // The ID from a child spawned by fork() is 0
#define ERROR -1 // Increasing readability when checking returns from read(), write(), fork(), pipe() etc.

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

#include "sys/wait.h" // getpid(), getppid()

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

#include <errno.h> // Provide multiple macros used for error conditions

// int	main(void)
// {
// 	int	id1 = fork();
// 	int	id2 = fork();
// 	int	i = 0;
// 	if (id1 == 0)
// 	{
// 		if (id2 == 0)
// 			printf("Hello from process Y.\n");
// 		else
// 			printf("Hello from process X.\n");
// 	}
// 	else
// 	{
// 		if (id2 == 0)
// 			printf("Hello from process Z.\n");
// 		else
// 			printf("Hello from the parent process.\n");
// 	}
// 	while(wait(NULL) != -1 || errno != ECHILD)
// 		printf("Waited for a child to finish\n");
// 	return (0);
// }

// Comunicating between processes using pipes

// int	main(void)
// {
// 	int fd[2]; // fd[0] - read | fd[1] - write
// 	if (pipe(fd) == -1)
// 		return (printf("An error occured with opening the pipe\n"), -1);
// 	int id = fork();
// 	if (id == 0)
// 	{
// 		close(fd[0]);
// 		int	x;
// 		printf("Input a number: ");
// 		scanf("%i", &x);
// 		if (write(fd[1], &x, sizeof(int)) == -1)
// 			return (printf("An error occured with writing to the pipe\n"), -1);
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		int	y;
// 		if (read(fd[0], &y, sizeof(int)) == -1)
// 			return (printf("An error occured with reading from the pipe\n"), -1);
// 		close(fd[0]);
// 		printf("Got from child process: %i\n", y);
// 		wait(NULL);
// 	}
// 	return (0);
// }

// A practical case using fork() and pipe()

// int	main(void)
// {
// 	int	arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
// 	int	arrSize = sizeof(arr) / sizeof(int);
// 	int	start, end;
// 	int	fd[2];
// 	if (pipe(fd) == ERROR)
// 		return (1);
// 	int	id = fork();
// 	if (id == -1)
// 		return (1);
// 	if (id == 0)
// 	{
// 		start = 0;
// 		end = arrSize / 2;
// 	}
// 	else
// 	{
// 		start = arrSize / 2;
// 		end = arrSize;
// 	}
// 	int	sum = 0;
// 	int	i = start;
// 	while (i < end)
// 		sum += arr[i++];
// 	printf("Calculated partial from ");
// 	if (id == CHILD)
// 		printf("child: %i\n", sum);
// 	else
// 		printf("parent: %i\n", sum);
// 	if (id == CHILD)
// 	{
// 		close(fd[0]);	
// 		if (write(fd[1], &sum, sizeof(sum)) == ERROR)
// 			return (1);
// 		close(fd[1]);	
// 	}
// 	else
// 	{
// 		int sumFromChild;
// 		close(fd[1]);
// 		if (read(fd[0], &sumFromChild, sizeof(sumFromChild)) == ERROR)
// 			return (1);
// 		close(fd[0]);
// 		int	totalSum = sum + sumFromChild;
// 		printf("Total sum: %i\n", totalSum);
// 	}
// 	wait(NULL);
// 	return (0);
// }

// Two way communication between processes

#include <time.h> // Brings srand() randomization function

// int	main(void)
// {
// 	int	p1[2]; // Child -> Parent Pipe
// 	int	p2[2]; // Parent -> Child Pipe

// 	if (pipe(p1) == ERROR)
// 		return (1);
// 	if (pipe(p2) == ERROR)
// 		return (1);

// 	int pid = fork();
// 	if (pid == ERROR)
// 		return (1);

// 	if (pid == CHILD) // Child process
// 	{
// 		close(p1[0]);
// 		close(p2[1]);
// 		int	x;
// 		if (read(p2[0], &x, sizeof(x)) == ERROR)
// 			return (1);
// 		fprintf(stderr, "Received %i\n", x);
// 		x *= 4;
// 		if (write(p1[1], &x, sizeof(x)) == ERROR)
// 			return (1);
// 		fprintf(stderr, "Wrote %i\n", x);
// 		close(p1[1]);
// 		close(p2[0]);
// 	}

// 	else // Parent process
// 	{
// 		close(p1[1]);
// 		close(p2[0]);
// 		srand(time(NULL));
// 		int	y = rand() % 10;
// 		if (write(p2[1], &y, sizeof(y)) == ERROR)
// 			return (1);
// 		printf("Wrote %i\n", y);
// 		if (read(p1[0], &y, sizeof(y)) == ERROR)
// 			return (1);
// 		printf("Result is %i\n", y);
// 		wait(NULL);
// 		close(p1[0]);
// 		close(p2[1]);
// 	}
// 	return (0);
// }

// Executing commands
// int	main(void)
// {
// 	int	pid = fork();
// 	if (pid == ERROR)
// 		return (1);
// 	if (pid == CHILD)
// 		execlp("ping", "ping", "-c", "3", "google.com", NULL);
// 	else
// 	{
// 		wait(NULL);
// 		printf("\nSuccess!\n\n");
// 	}
// 	return (0);
// }

// Getting exit status code
int	main(void)
{
	int	pid = fork();
	if (pid == ERROR)
		return (1);
	if (pid == CHILD)
	{
		int err = execlp("pingr", "ping", "-c", "3", "google.com", NULL);
		if (err == -1)
			return (printf("Could not find program to execute!\n"), 0);
	}
	else
	{
		int	wstatus;
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			int statusCode = WEXITSTATUS(wstatus);
		}
		printf("\nSuccess!\n\n"); 
	}
	return (0);
}