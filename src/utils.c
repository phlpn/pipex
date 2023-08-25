/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:36:22 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/25 13:40:31 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_mgmt(char *msg, int exit_code)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	exit(exit_code);
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

char	*getenvp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == TRUE)
			return (envp[i] + 5);
	return (NULL);
}

char	*getcmdp(char *cmd, char **envp)
{
	char	**tokens;
	char	*cmd_path;
	int		i;

	tokens = ft_split(getenvp(envp), ':');
	if (!tokens)
		exit_mgmt("Error: split failed\n", EXIT_FAILURE);
	i = 0;
	cmd = ft_strjoin("/", cmd);
	if (cmd == NULL)
		exit_mgmt("Error: strjoin failed\n", EXIT_FAILURE);
	while (tokens[i])
	{
		cmd_path = ft_strjoin(tokens[i], cmd);
		if (cmd_path == NULL)
			exit_mgmt("Error: strjoin failed\n", EXIT_FAILURE);
		if (access(cmd_path, F_OK) == TRUE)
			return (ft_free_split(tokens), free(cmd), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_split(tokens), free(cmd_path), free(cmd), NULL);
}
