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
#include "printf.h"
//$> ./pipex infile "ls -l" "wc -l" outfile
int main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		infile;
	int		outfile;
	char	*bin;
	t_command	*command;

	if (argc != 5)
		return (-1);
	if (permitions(argv[1], argv[4]) == -1)
		return (-1);
	pipe(fd);
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_WRONLY);
	command = fill_command(argv[2], envp);
	piped_child(fd[1], infile, fd[0], command);
	command = fill_command(argv[3], envp);
	piped_child(outfile, fd[0], fd[1], command);
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
	t_command *command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->args = ft_split(args, ' ');
	if (!command->args)
		return (free(command), NULL);
	command->bin = get_path(envp, command->args[0]);
	if (!command->bin)
		return (free(command), NULL);
	return (command);
}
