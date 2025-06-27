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
#include "libft.h"
#include <fcntl.h>
#include <stdio.h> 
#include <unistd.h>
//$> ./pipex infile "ls -l" "wc -l" outfile

char	*reading_from_stdin(char *cmd);
int		call_command_to_fd(int infile, int outfile, char *cmd, char **envp);

int	call_command_to_fd(int infile, int outfile, char *cmd, char **envp)
{
	int			fd[2];
	t_command	*command;

	command = fill_command(cmd, envp);
	if (outfile == -1)
		if (pipe(fd) == -1)
			return (ft_putstr_fd("Pipe failed\n", 2), -1);
	if (command != NULL && outfile == -1)
		piped_child(fd[1], infile, fd[0], command);
	else if (command != NULL)
	{
		if (piped_child(outfile, infile, -1, command) == -1)
			return (ft_putstr_fd("Child failed \n", 2), -1);
	}
	else
		(ft_putstr_fd("Invalid command", 2),
			ft_putstr_fd(cmd, 2), ft_putstr_fd("\n", 2));
	if (outfile == -1 && close(fd[1]) != 2 && close(infile) != 2)
		return (fd[0]);
	close(infile);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;
	int	i;
	int	executed;

	executed = 0;
	intputcheck(argc, argv, envp);
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		return (ft_putstr_fd("Failed to open infile\n", 2), 1);
	i = 2;
	while (i < argc - 2)
	{
		infile = call_command_to_fd(infile, -1, argv[i], envp);
		if (i++ && infile != -1)
			executed++;
	}
	outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (outfile == -1)
		return (close(infile), -1);
	if (call_command_to_fd(infile, outfile, argv[i], envp) != -1)
		executed ++;
	return (wait_x_times(executed), 1);
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
		return (free_split(&(command->args)), free(command), NULL);
	return (command);
}

void	free_command(t_command **command)
{
	free_split(&((*command)->args));
	free((*command)->bin);
	free(*command);
	*command = NULL;
}
