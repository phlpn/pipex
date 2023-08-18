/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnixProcesses.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:07:50 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/18 15:40:15 by alexphil         ###   ########.fr       */
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

#include "sys/wait.h" // getpid(), getppid(), WIFEXITED

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
// int	main(void)
// {
// 	int	pid = fork();
// 	if (pid == ERROR)
// 		return (1);
// 	if (pid == CHILD)
// 	{
// 		int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
// 		if (err == ERROR)
// 			return (printf("Could not find program to execute!\n"), 1);	
// 	}
// 	else
// 	{
// 		int	wstatus;
// 		wait(&wstatus);
// 		if (WIFEXITED(wstatus)) // Check specific bit(s) from wstatus to know if Child exited / ended correctly
// 		{
// 			int statusCode = WEXITSTATUS(wstatus); // Check another specific bit(s) from wstatus to get the return value from Child
// 			if (statusCode == 0)
// 				printf("\nSuccess!\n");
// 			else
// 				printf("\nError %i.\n", statusCode);
// 		}
// 	}
// 	return (0);
// }

// Executing another program [Less relatable as Pipex must use execve() and not execl() !] using the env
// int	main(int ac, char **av, char **envp)
// {
// 	int i = -1;
// 	while (envp[++i])
// 		printf("%s\n", envp[i]);
// 	return (0);
// }

#include <fcntl.h>

// Redirecting Standad Output
// int	main(void)
// {
// 	int	pid = fork();
// 	if (pid == ERROR)
// 		return (1);
// 	if (pid == CHILD)
// 	{
// 		int	file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
// 		if (file == ERROR)
// 			return (1);
// 		printf("The original fd to pingResults: %i\n", file);
// 		dup2(file, STDOUT_FILENO);
// 		close(file);
		
// 		int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
// 		if (err == ERROR)
// 			return (printf("Could not find program to execute!\n"), 1);	
// 	}
// 	else
// 	{
// 		int	wstatus;
// 		wait(&wstatus);
// 		if (WIFEXITED(wstatus)) // Check specific bit(s) from wstatus to know if Child exited / ended correctly
// 		{
// 			int statusCode = WEXITSTATUS(wstatus); // Check another specific bit(s) from wstatus to get the return value from Child
// 			if (statusCode == 0)
// 				printf("\nSuccess!\n");
// 			else
// 				printf("\nError %i.\n", statusCode);
// 		}
// 	}
// 	return (0);
// }

#include <signal.h> // kill(), SIGKILL / SIGSTOP / SIGCONT macros

// Introduction to signals
// int	main(void)
// {
// 	int	pid = fork();
// 	if (pid == -1)
// 		return (1);
	
// 	if (pid == CHILD)
// 	{
// 		while (1)
// 		{
// 			printf("Some text goes here\n");
// 			usleep(50000);
// 		}
// 	}
// 	else
// 	{
// 		int	t;
// 		kill(pid, SIGSTOP);
// 		do
// 		{
// 			printf("Time in seconds for execution: ");
// 			scanf("%d", &t);

// 			if (t > 0)
// 				kill(pid, SIGCONT);
// 				sleep(t);
// 				kill(pid, SIGSTOP);
// 		} while (t > 0);
		
// 		kill(pid, SIGKILL);
// 		wait(NULL);
// 	}
// 	return (0);
// }

// Background and foreground process 
// ...

// Handling signals
// ...

// Communicating between processes using signals
// int	x = 0;

// void	handle_sigusr1(int sig)
// {
// 	if (x == 0)
// 		printf("\nHint: Remember that mulitplicaion is repetitive addition!\n");
// }

// int	main(void)
// {
// 	int	pid = fork();
// 	if (pid == ERROR)
// 		return (1);
	
// 	if (pid == CHILD)
// 	{
// 		sleep(5);
// 		kill(getppid(), SIGUSR1);
// 	}
// 	else
// 	{
// 		struct sigaction sa = { 0 };
// 		sa.sa_flags = SA_RESTART;
// 		sa.sa_handler = &handle_sigusr1;
// 		sigaction(SIGUSR1, &sa, NULL);
		
// 		printf("What is the result of 3 x 5: ");
// 		scanf("%d", &x);
// 		if (x == 15)
// 			printf("Right!\n");
// 		else
// 			printf("Wrong!\n");
// 		wait(NULL);
// 	}
// }

// How to send an array through a pipe
// int	main(void)
// {
// 	int	fd[2];
// 	if (pipe(fd) == ERROR)
// 		return (1);
// 	int	pid = fork();
// 	if (pid == CHILD)
// 	{
// 		close(fd[0]);
// 		int	n;
// 		int	arr[10];
// 		srand(time(NULL));
// 		n = rand() % 10 + 1;
// 		printf("Generated: ");
// 		int i = -1;
// 		while (++i < n)
// 		{
// 			arr[i] = rand() % 11;
// 			printf("%i ", arr[i]);
// 		}
// 		printf("\n");
// 		if (write(fd[1], &n, sizeof(int)) == ERROR)
// 			return (1);
// 		printf("Sent size of array: %i\n", n);
// 		if (write(fd[1], arr, sizeof(int) * n) == ERROR)
// 			return (1);
// 		printf("Sent array\n");
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		int	arr[10];
// 		int	n, i = 0, sum = 0;
// 		if (read(fd[0], &n, sizeof(int)) == ERROR)
// 			return (1);
// 		printf("Received size of array: %i\n", n);
// 		if (read(fd[0], arr, sizeof(int) * n) == ERROR)
// 			return (1);
// 		printf("Received array\n");
// 		close(fd[0]);
// 		while (i < n)
// 			sum += arr[i++];
// 		printf("Sum of the array is %i\n", sum);
// 		wait(NULL);
// 	}
// 	return (0);
// }

#include <string.h> // Used for strlen() function

// How to send a string through a pipe
// int	main(void)
// {
// 	int	fd[2];
// 	if (pipe(fd) == ERROR)
// 		return (1);
// 	int	pid = fork();
// 	if (pid == ERROR)
// 		return (1);
// 	if (pid == CHILD)
// 	{
// 		close(fd[0]);
// 		char	str[200];
// 		printf("Input string: ");
// 		fgets(str, 200, stdin);
// 		str[strlen(str) - 1] = '\0';
// 		int	len = strlen(str) + 1;
// 		if (write(fd[1], &len, sizeof(len)) == ERROR)
// 			return (1);
// 		if (write(fd[1], str, sizeof(char) * len))
// 			return (1);
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		char str[200];
// 		int	len;
// 		if (read(fd[0], &len, sizeof(len)) == ERROR)
// 			return (1);
// 		if (read(fd[0], str, sizeof(char) * len) == ERROR)
// 			return (1);
// 		printf("Received string: \"%s\"\n", str);
// 		close(fd[0]);
// 		wait(NULL);
// 	}
// }

// Simulating the pipe '|' operator
// ...
