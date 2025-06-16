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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// outputfd  if where shit should be writen
// filefd is where we get shit from
// command says what should we do with it
// creates a child that needs to be piped beforehand
int	piped_child(int outfile, int  infile, int lose, char **command)
{
	char	*program;
	char	*args[4];
	char	*env[1];
	int		f;

	
	args[0] = command[0];
	args[1] = command[1];
	args[2] = NULL;
	args[3] = NULL;
	*env = NULL;
	f = fork();
	if (f == 0)
	{
		close(lose);
		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		if (execve(args[0], args, env) == -1)
		{
		ft_printf("errror\n");
			close(infile);
			close(outfile);
			return (0);
		}
		return (-1);
	}
	waitpid(1, &f, 0);
	return (1);
}

