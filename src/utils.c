/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:36:22 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/23 16:58:15 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_mgmt(char *msg, int exit_code)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	exit(exit_code);
}

int	open_file(char *file, t_flow flow)
{
	int	fd;

	if (flow == INPUT)
		fd = open(file, O_RDONLY, 0777);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == ERROR)
		exit_mgmt("Error: file not found\n", EXIT_FAILURE);
	return (fd);
}

char	*getenvp(char **envp)
{
	char	*trg;
	int		i;
	int		j;

	trg = "PATH=";
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (trg[j] && trg[j] == envp[i][j])
			j++;
		if (trg[j] == '\0' && envp[i][j] == '/')
			return (envp[i] + j);
		i++;
	}
	return (NULL);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*getcmdp(char *cmd, char **envp)
{
	char	*paths;
	char	**tokens;
	char	*cmd_path;
	int		i;

	paths = getenvp(envp);
	tokens = ft_split(paths, ':');
	if (!tokens)
		exit_mgmt("Error: malloc failed\n", EXIT_FAILURE);
	i = 0;
	while (tokens[i])
	{
		cmd_path = ft_strjoin(tokens[i], "/");
		if (cmd_path == NULL)
			exit_mgmt("Error: malloc failed\n", EXIT_FAILURE);
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (cmd_path == NULL)
			exit_mgmt("Error: malloc failed\n", EXIT_FAILURE);
		if (access(cmd_path, F_OK) == TRUE)
			return (ft_free_split(tokens), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_split(tokens), NULL);
}
