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
	char	*binpath
	
	if (argc != 5)
		return (-1);
	if (permitions(argv[1], argv[4]) == -1)
		return (-1);
	binpath = get_path(envp, argv[2]);
	pipe(fd);
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_WRONLY);
	piped_child(fd[1], infile, fd[0],binpath);
	read(fd[1],str,13);
	binpath = get_path(envp, argv[3]);
	piped_child(outfile, fd[0], fd[1], binpath);

	
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
