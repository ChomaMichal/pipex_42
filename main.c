/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:05:29 by mchoma            #+#    #+#             */
/*   Updated: 2025/06/09 16:05:33 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include <stdio.h>
//$> ./pipex infile "ls -l" "wc -l" outfile
int	main(int argc, char **argv, char **envp)
{
	int			fd[2];
	int			infile;
	int			outfile;
	t_command	*command;

	if (argc != 5)
		return (-1);
	pipe(fd);
	outfile = permitions(argv[1], argv[4]);
	printf("%i outifle\n", outfile);
	infile = open(argv[1], O_RDONLY);
	if (outfile == -1 || infile == -1)
		return (-1);
	command = fill_command(argv[2], envp);
	if (command == NULL)
		return (-1);
	piped_child(fd[1], infile, fd[0], command);
	command = fill_command(argv[3], envp);
	if (command == NULL)
		return (-1);
	piped_child(outfile, fd[0], fd[1], command);
	return (1);
}

//permitions testee
int	permitions(char *rd, char *wr)
{
	if (access(rd, R_OK) == -1)
		return (-1);
	if (access(wr, F_OK) == -1)
	{
		return (open(wr, O_CREAT, 0644));
	}
	if (access(wr, W_OK) == -1)
		return (-1);
	return (open(wr, O_TRUNC | O_WRONLY));
}

t_command	*fill_command(char *args, char **envp)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->args = ft_split(args, ' ');
	if (!command->args)
		return (free(command), NULL);
	command->bin = get_path(envp, command->args[0]);
	if (!command->bin)
		return (free_split(&(command->args)), free(command),  NULL);
	return (command);
}

void	free_command(t_command **command)
{
	free_split(&((*command)->args));
	free((*command)->bin);
	free(*command);
	*command = NULL;
}
