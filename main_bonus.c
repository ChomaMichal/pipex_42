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

void	close_fds(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1)
		close(fd1);
	if (fd2)
		close(fd2);
	if (fd3)
		close(fd3);
	if (fd4)
		close(fd4);
}

int	here_doc(int argc, char **argv, char **envp)
{
	char		*tmp;
	ssize_t		rt;
	int			fd[4];
	t_command	*command;
	int			outfile;

	
	if (access(argv[argc - 1], W_OK) == -1)
		exit(1);
	command = fill_command(argv[3], envp);
	tmp = ft_calloc(sizeof(char), 1024); // free command when tmp fails and the other way
	if (command == NULL || tmp == NULL)
			exit(1);
	pipe(fd + 2);
	pipe(fd);
	piped_child_b(fd[1], fd[2], fd, command);
	command = fill_command(argv[4], envp);
	outfile = open(argv[argc -1], O_WRONLY);
	piped_child_b(outfile, fd[0], fd, command);
	argv[2] = ft_strjoin(argv[2], "\n");
	if (argv[2] == NULL) //freestuff
		exit(0);
	while(1)
	{
		rt = read(0, tmp, 1023);
		if (rt == -1)
			exit (0);
		if (ft_strnstr(tmp, argv[2], 1024))
			break ;
		rt = write(fd[3], tmp, rt);
		if (rt == -1)
			exit (-1);
	}
	close_fds(fd[0], fd[1], fd[2], fd[3]);
	close(outfile);
	free(argv[2]);
	free(tmp);
	waitpid(-1, NULL, 0);
	exit(0);
}


int	main(int argc, char **argv, char **envp)
{
	int			fd[2];
	int			infile;
	int			outfile;
	t_command	*command;
	int			i;
	
	if (argc < 4)
		return 1;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		return (here_doc(argc, argv, envp));
	if (permitions(argv[1], argv[argc -1]) == -1)
		return (-1);
	fd[0] = 0;
	fd[1] = 0;
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		return (1);
	i = 0;
	while (i < argc - 4)
	{
		command = fill_command(argv[i + 2], envp);
		if (command == NULL && close (infile))
			exit(1);
		pipe(fd);
		piped_child(fd[1], infile, fd[0], command);
		close(fd[1]);
		close(infile);
		infile = fd[0];
		i ++;
	}
	outfile = open(argv[argc - 1], O_WRONLY);
	if (outfile== -1)
		return (close(infile), -1);
	command = fill_command(argv[argc - 2], envp);
	if (command == NULL)
		return (close(outfile), close(infile),-1);
	piped_child(outfile, infile, 0, command);
	close(infile);
	close(outfile);
	i = 0;
	while(i ++ < argc - 2)
		waitpid(-1, NULL, 0);
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


