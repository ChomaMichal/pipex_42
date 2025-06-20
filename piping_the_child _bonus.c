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
// creates a child that
int	piped_child_b(int outfile, int infile, int *lose,t_command *command)
{
	int		f;
	int		i;
	
	i = 0;
	f = fork();
	if (f == 0)
	{
		perror("entered child\n");
		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
//		while(i < 5 && i ++ && lose[i - 1] != infile && lose[i-1] != outfile)
//			close(lose[i -1]);
		close(lose[0]);
		close(lose[1]);
		if (execve(command->bin, command->args, NULL) == -1)
		{
			perror("execve failed\n");
			printf("errror\n");
			free_command(&command);
			exit(0);
		}
		return (-1);
	}
	perror("exited piped child\n");
	free_command(&command);
	return (1);
}
