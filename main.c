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
//$> ./pipex infile "ls -l" "wc -l" outfile
int main(int argc, char **argv)
{
	int		fd[2];
	char	*str = ft_calloc(1024, 1);

	if (argc != 5)
		return (-1);

	if (permitions(argv[1], argv[4]) == -1)
		return (-1);
	pipe(fd);
	piped_child(fd[1], argv[1], argv[2]);
	//this aplied the funcion to first file
		
	read(fd[0], str, 1024);
	ft_printf("31 bashed file1 %s \n", str);
	return (1);
}


//permitions testeed
int	permitions(char *read, char *write)
{
	if (access(read, R_OK) == -1)
		return (-1);
	if (access(write, W_OK) == -1)
		return (-1);
	return (1);
}
