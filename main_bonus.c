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

char	*reading_from_stdin(int fd, char *cmd);
int	call_command_to_fd(int infile, int outfile, char *cmd, char **envp);

char	*ft_strjoinf1(char *fr, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(fr, str);
	free(fr);
	return (tmp);
}

char *format_doc(char *str)
{
	char	*tmp;

	tmp = ft_strjoin("\n", str);
	if (tmp == NULL)
		return (ft_putstr_fd("malloc failed\n", 2), NULL);
	return (ft_strjoinf1(tmp, "\n"));
}


int	reading_command_line(char **argv)
{
	char		tmp[1025];
	char		*str;
	int			fd;

	str = NULL;
	argv[2] = format_doc(argv[2]);
	if(argv[2] == NULL)
		return (-1);
	fd = open("/tmp/tmp.tmp", O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		return (ft_putstr_fd("file creation failed\n", 2), free(argv[2]),-1);
	str = reading_from_stdin(fd, argv[2]);
	if (write(fd, str, ft_strlen(str)) == -1)
	{
		return (ft_putstr_fd("write failed\n", 2) , close(fd), free(str), free(argv[2]), -1);
	}
	return (free(str), free(argv[2]), fd);
}

char	*reading_from_stdin(int fd, char *cmd)
{
	ssize_t		rd;
	char		*str;
	char		tmp[1025];

	str = NULL;
	while(1)
	{
		rd = read(0, tmp, 1024);
		if(rd == -1)
			return (ft_putstr_fd("read failed\n", 2), free(str), free(cmd), NULL);
		tmp[rd] = 0;
		if (rd == 0)
			return (str);	
		str = ft_strjoinf1(str, tmp);
		if (str == NULL)
			return (ft_putstr_fd("malloc failed\n", 2), free(cmd), NULL);
		if (ft_strnstr(str, cmd, ft_strlen(str)) != NULL ||
			ft_strnstr(str, cmd + 1, ft_strlen(cmd + 1)) != NULL)
		{	
			str[ft_strlen(str) - ft_strlen(cmd) + 1] = 0;
			return (str);
		}
	}
	return (NULL);
}

void	hexit(char *file, char *str, int code)
{
	if(file)
		unlink(file);
	if(str)
		ft_putstr_fd(str, 2);
	exit(code);
}

void	here_doc(int argc, char **argv, char **envp)
{
	int			fd[2];
	int			infile;
	int			outfile;
	int			i;
	int			executed;
	
	if (permitions(NULL, argv[argc -1]) == -1)
		hexit (NULL, NULL, 1);
	reading_command_line(argv);
	infile = open("/tmp/tmp.tmp", O_RDONLY);
	if (infile == -1)
		hexit ("/tmp/tmp.tmp", "Failed to open tmpfile\n", 1);
	while (i < argc - 2)
	{
		infile = call_command_to_fd(infile, -1, argv[i], envp);
		if (i++ && infile != -1)
			executed++;
	}
	outfile = open(argv[argc - 1], O_WRONLY | O_APPEND);
	if (outfile== -1)
		hexit ("/tmp/tmp.tmp", "Failed to open outfile\n", 1);
	if (call_command_to_fd(infile, -1, argv[i], envp) != -1)
		executed ++;
	hexit ("/tmp/tmp.tmp", NULL, 1);
}

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
		if(piped_child(outfile, infile, -1, command) == -1)
			return (ft_putstr_fd("Child failed \n", 2), -1);
	}
	else
		(ft_putstr_fd("Invalid command", 2), ft_putstr_fd(cmd, 2), ft_putstr_fd("\n", 2));
	if (outfile == -1 && close(fd[1]) != 2 && close(infile) != 2)
		return (fd[0]);
	close(infile);
	return (0);
}

void	wait_x_times(int i)
{
	while(i)
	{
		waitpid(-1, NULL, 0);
		i --;
	}
}

void	intputcheck(int argc, char **argv, char **envp)
{
	if (argc < 4)
	{
		ft_putstr_fd("Not enought arguments", 2);
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		 here_doc(argc, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
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
	outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	if (outfile == -1)
		return (close(infile), -1);
	if (call_command_to_fd(infile, -1, argv[i], envp) != -1)
		executed ++;
	return (wait_x_times(executed), 1);
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


