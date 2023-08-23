/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:36:22 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/23 11:34:16 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_mgmt(char *msg, int exit_code)
{
	write(2, msg, strlen(msg));
	exit(exit_code);
}

int	open_file(char *file, t_flow flow)
{
	int	fd;

	if (flow == IN)
		fd = open(file, O_RDONLY, 0777);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit_mgmt("Error: file not found\n", 1);
	return (fd);
}

char	*getenvp(char *name, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (name[j] && name[j] == envp[i][j])
			j++;
		if (name[j] == '\0' && envp[i][j] == '=')
			return (envp[i] + j + 1);
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
	char	*path;
	char	**path_list;
	char	*cmd_path;
	int		i;

	path = getenvp("PATH", envp);
	path_list = ft_split(path, ':');
	i = -1;
	while (path_list[++i])
	{
		cmd_path = ft_strjoin(path_list[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			ft_free_split(path_list);
			return (cmd_path);
		}
		free(cmd_path);
	}
	ft_free_split(path_list);
	return (NULL);
}
