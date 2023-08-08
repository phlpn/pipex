/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:45:18 by alexphil          #+#    #+#             */
/*   Updated: 2023/08/08 14:45:43 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	nb_word(char const *s, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			nb++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (nb);
}

static size_t	ln_word(char const *s, char c, size_t i)
{
	size_t	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static void	*ft_free(char **strs, size_t j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	ssize_t	size;
	char	**strs;
	ssize_t	i;
	ssize_t	j;
	size_t	len;

	size = nb_word(s, c);
	strs = malloc((size + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < size)
	{
		while (s[i] == c)
			i++;
		len = ln_word(s, c, i);
		strs[j] = ft_substr(s, i, len);
		if (!strs[j])
			if (!ft_free(strs, j))
				return (NULL);
		i += len;
	}
	strs[j] = NULL;
	return (strs);
}
