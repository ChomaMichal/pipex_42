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
//
int	main(int argc, char **argv, char **envp)
{
	int			fd[2];
	int			ft[2];
	int			infile;
	int			outfile;
	t_command	*command;
	int i = 0;

	if (permitions(argv[1], argv[argc -1]) == -1)
		return (-1);
	perror("passed permitions\n");
	pipe(fd);
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[argc - 1], O_WRONLY);
	if (outfile == -1 || infile == -1)
		return (-1);
	perror("oppened files\n");
	command = fill_command(argv[2], envp);
	if (command == NULL)
		return (-1);
	piped_child(fd[1], infile, fd[0], command);
	free_command(&command);
	perror("first command\n");
	
	command = fill_command(argv[3], envp);
	if (command == NULL)
		return (-1);
	pipe(ft);
	close(fd[1]);
	piped_child(ft[1], fd[0], ft[0], command);
	free_command(&command);
	perror("second command\n");


	close(ft[1]);
	command = fill_command(argv[4], envp);
	if (command == NULL)
		return (-1);
	piped_child(outfile, ft[0], ft[1], command);
	free_command(&command);
	perror("thid command\n");
	close(fd[0]);
	close(ft[0]);
	close(ft[1]);
	close(fd[1]);

	while(i ++ < 3)
	{
		sleep(5);
		waitpid(-1, NULL, 0);
	}
	return (1);
}

//permitions testee
int	permitions(char *read, char *write)
{
	if (access(read, R_OK) == -1)
		return (-1);
	if (access(write, W_OK) == -1)
		return (-1);
	return (1);
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
