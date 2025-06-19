/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:24:04 by mchoma            #+#    #+#             */
/*   Updated: 2025/06/19 12:24:06 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

char	*isbin(char *path, char *command)
{
	char	*binpath;
	char	*tmp;

	if (command == NULL || path == NULL)
		return (NULL);
	tmp = ft_strjoin("/", command);
	if (!tmp)
		return (NULL);
	binpath = ft_strjoin(path, tmp);
	free(tmp);
	if (binpath)
	{
		if (access(binpath, X_OK) == 0)
			return (binpath);
	}
	free(binpath);
	return (NULL);
}

void	free_split(char ***split)
{
	int		i;

	i = 0;
	while (split && (*split) && (*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
}

char	*get_path(char**envp, char *command)
{
	int		i;
	int		j;
	char	**arr;
	char	*path;

	arr = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			arr = ft_split(envp[i] + 5, ':');
			j = 0;
			while (arr && arr[j])
			{
				path = isbin(arr[j], command);
				if (path)
					return (free_split(&arr), path);
				j++;
			}
		}
		i ++;
	}
	return (free_split(&arr), NULL);
}
