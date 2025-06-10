/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_the_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:05:23 by mchoma            #+#    #+#             */
/*   Updated: 2025/06/09 16:05:24 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// outputfd  if where shit should be writen
// filefd is where we get shit from
// command says what should we do with it
// creates a child that needs to be piped beforehand
int	piped_child(int fd, char *file, char* command)
{
	char	*program;
	char	*args[4];
	char	*env[1];
	int		f;

//	program = "/run/current-system/sw/bin/bash";
	program = "/usr/bin/bash";
//	args = {program, "-c",  command, NULL};
	args[0] = program;
	args[1] = "-c";
	args[2] = ft_strjoin(command, ft_strjoin(" ",file));
	args[3] = NULL;
//	*env = NULL;
	//ft_printf();
	f = fork();
	if (f == 0)
	{
			dup2(fd, 1);
		if (execve(program, args, env) == -1)
		{
			close(fd);
			return (-1);
		}
		return (-1);
	}
	else
	{
	//ft_printf("49return piped child\n");
	waitpid(1, &f, 0);
//	waitpid(1, &f, 0);
	return (1);
	}
}

