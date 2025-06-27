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
int	piped_child(int outfile, int infile, int lose, t_command *command)
{
	int		f;

	f = fork();
	if (f == 0)
	{
		if (lose != -1)
			close(lose);
		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(infile);
		close(outfile);
		if (execve(command->bin, command->args, NULL) == -1)
		{
			close(infile);
			close(outfile);
			free_command(&command);
			exit(0);
		}
		return (-1);
	}
	free_command(&command);
	return (f);
}
