/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:37:43 by mchoma            #+#    #+#             */
/*   Updated: 2025/06/27 17:37:46 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	hexit(char *file, char *str, int code)
{
	if (file)
		unlink(file);
	if (str)
		ft_putstr_fd(str, 2);
	exit(code);
}

int	wait_x_times(int i, int rt)
{
	int	idk;

	i --;
	if (rt != -1)
		waitpid(rt, &idk, 0);
	while (i)
	{
		waitpid(-1, 0, 0);
		i --;
	}
	if (rt != -1)
	{
		if (WIFSIGNALED(idk))
			return (WTERMSIG(idk) + 128);
		WEXITSTATUS(idk);
		return (WEXITSTATUS(idk));
	}
	return (1);
}

void	intputcheck(int argc, char **argv, char **envp)
{
	if (argc < 4)
	{
		ft_putstr_fd("Not enought arguments\n", 2);
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		here_doc(argc, argv, envp);
}

int	permitions(char *rd, char *wr)
{
	int	fd;

	if (rd != NULL && access(rd, R_OK) == -1)
		return (-1);
	if (access(wr, F_OK) == -1)
	{
		fd = open(wr, O_CREAT, 0644);
		if (fd == -1)
			return (-1);
		return (close(fd));
	}
	if (access(wr, W_OK) == -1)
		return (-1);
	return (1);
}

char	*ft_strjoinf1(char *fr, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(fr, str);
	free(fr);
	return (tmp);
}
