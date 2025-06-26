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
		return (NULL);
	return (ft_strjoinf1(tmp, "\n"));
}


int	reading_command_line(char **argv)
{
	char		tmp[1025];
	char		*str;
	ssize_t		rd;
	int			fd;

	str = NULL;
	argv[2] = format_doc(argv[2]);
	if(argv[2] == NULL)
		return (-1);
	fd = open("/tmp/tmp.tmp", O_CREAT | O_RDWR, 0666);
	while(1)
	{
		rd = read(0, tmp, 1024);
		if(rd == -1)
			return (free(str), free(argv[2]), -1);
		tmp[rd] = 0;
		if (rd == 0)
			break;
		str = ft_strjoinf1(str, tmp);
		if (str == NULL)
			return (free(argv[2]), -1);
		if (ft_strnstr(str, argv[2], ft_strlen(str)) != NULL ||
			ft_strnstr(str, argv[2] + 1, ft_strlen(argv[2] + 1)) != NULL)
		{	
			str[ft_strlen(str) - ft_strlen(argv[2]) + 1] = 0;
			break ;
		}
	}
	if (write(fd, str, ft_strlen(str)) == -1)
	{
		return (close(fd), free(str), free(argv[2]), -1);
	}
	return (free(str), free(argv[2]), fd);
}

int	here_doc(int argc, char **argv, char **envp)
{
	int			fd[2];
	int			infile;
	int			outfile;
	t_command	*command;
	int			i;
	
	if (permitions(NULL, argv[argc -1]) == -1)
		return (-1);
	reading_command_line(argv);
	infile = open("/tmp/tmp.tmp", O_RDONLY);
	if (infile == -1)
		exit (1);
	i = 3;
	while (i < argc - 2)
	{
		command = fill_command(argv[i], envp);
		if (command == NULL)
			exit(1);
		pipe(fd);
		piped_child(fd[1], infile, fd[0], command);
		close(fd[1]);
		close(infile);
		infile = fd[0];
		i ++;
	}
	outfile = open(argv[argc - 1], O_WRONLY | O_APPEND);
	if (outfile== -1)
		exit(1);
	command = fill_command(argv[argc - 2], envp);
	if (command == NULL)
		return (close(outfile), close(infile),-1);
	piped_child(outfile, infile, 0, command);
	close(infile);
	close(outfile);
	i = 0;
	while(i ++ < argc - 5)
		waitpid(-1, NULL, 0);
	unlink("/tmp/tmp.tmp");
	exit(1);
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
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		return (1);
	i = 2;
	while (i < argc - 2)
	{
		command = fill_command(argv[i], envp);
		if (command == NULL)
			exit(1);
		pipe(fd);
		piped_child(fd[1], infile, fd[0], command);
		close(fd[1]);
		close(infile);
		infile = fd[0];
		i ++;
	}
	outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	if (outfile== -1)
		return (close(infile), -1);
	command = fill_command(argv[argc - 2], envp);
	if (command == NULL)
		return (close(outfile), close(infile),-1);
	piped_child(outfile, infile, 0, command);
	close(infile);
	close(outfile);
	i = 0;
	while(i ++ < argc - 3)
		waitpid(-1, NULL, 0);
	return (1);
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


