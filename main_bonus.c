/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:06:25 by mchoma            #+#    #+#             */
/*   Updated: 2025/06/28 16:06:27 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include "libft.h"
//$> ./pipex infile "ls -l" "wc -l" outfile

int	call_command_to_fd(int infile, int outfile, char *cmd, char **envp)
{
	int			fd[2];
	t_command	*command;
	int			rt;

	rt = 0;
	command = fill_command(cmd, envp);
	if (outfile == -1)
		if (pipe(fd) == -1)
			return (ft_putstr_fd("Pipe failed\n", 2), -1);
	if (command != NULL && outfile == -1)
		rt = piped_child(fd[1], infile, fd[0], command);
	else if (command != NULL)
	{
		rt = piped_child(outfile, infile, -1, command);
		if (rt == -1)
			return (ft_putstr_fd("Child failed \n", 2), -1);
	}
	else
		(ft_putstr_fd("Invalid command: ", 2),
			ft_putstr_fd(cmd, 2), ft_putstr_fd("\n", 2));
	if (outfile == -1 && close(fd[1]) != 2 && close(infile) != 2)
		return (fd[0]);
	close(infile);
	return (rt);
}

int	main(int argc, char **argv, char **envp)
{
	int	inf;
	int	outfile;
	int	i;
	int	executed;
	int	rt;

	executed = 0;
	intputcheck(argc, argv, envp);
	inf = open(argv[1], O_RDONLY);
	if (inf == -1)
		ft_putstr_fd("Failed to open inf\n", 2);
	i = 2;
	while (i < argc - 2)
	{
		if (inf != -1)
			inf = call_command_to_fd(inf, -1, argv[i], envp);
		inf *= (1 - (i++ && ((inf != -1 && ++ executed) || 1) && inf == -1));
	}
	outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (outfile == -1)
		return (close(inf), ft_putstr_fd("Failed to open outfile\n", 2), -1);
	rt = call_command_to_fd(inf, outfile, argv[argc - 2], envp);
	if (rt != -1)
		executed ++;
	return (wait_x_times(executed, rt));
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
