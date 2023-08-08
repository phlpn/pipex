/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:08:40 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/08 12:24:28 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// https://dev.to/herbievine/42-a-comprehensive-guide-to-pipex-5165
void	dup2_demo(void)
{
	int	fd;

	fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	printf("This is printed in example.txt\n");
}

void	access_demo(void)
{
	if (access("example.txt", R_OK) != -1)
		printf("I have permission to read\n");
	else
		printf("I don't have permission to read\n");
}
