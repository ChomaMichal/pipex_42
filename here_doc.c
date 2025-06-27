/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:49:39 by mchoma            #+#    #+#             */
/*   Updated: 2025/06/27 17:49:41 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

char	*format_doc(char *str)
{
	char	*tmp;

	tmp = ft_strjoin("\n", str);
	if (tmp == NULL)
		return (ft_putstr_fd("malloc failed\n", 2), NULL);
	return (ft_strjoinf1(tmp, "\n"));
}

char	*reading_from_stdin(char *cmd)
{
	ssize_t		rd;
	char		*str;
	char		tmp[1025];

	str = NULL;
	while (1)
	{
		rd = read(0, tmp, 1024);
		if (rd == -1)
			return (ft_putstr_fd("rd fl\n", 2), free(str), free(cmd), NULL);
		tmp[rd] = 0;
		if (rd == 0)
			return (str);
		str = ft_strjoinf1(str, tmp);
		if (str == NULL)
			return (ft_putstr_fd("malloc failed\n", 2), free(cmd), NULL);
		if (ft_strnstr(str, cmd, ft_strlen(str)) != NULL
			|| ft_strnstr(str, cmd + 1, ft_strlen(cmd + 1)) != NULL)
		{
			str[ft_strlen(str) - ft_strlen(cmd) + 1] = 0;
			return (str);
		}
	}
	return (NULL);
}

int	reading_command_line(char **argv)
{
	char		*str;
	int			fd;

	str = NULL;
	argv[2] = format_doc(argv[2]);
	if (argv[2] == NULL)
		return (-1);
	fd = open("/tmp/tmp.tmp", O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		return (ft_putstr_fd("file creation failed\n", 2), free(argv[2]), -1);
	str = reading_from_stdin(argv[2]);
	if (write(fd, str, ft_strlen(str)) == -1)
	{
		return (ft_putstr_fd("write failed\n", 2),
			close(fd), free(str), free(argv[2]), -1);
	}
	return (free(str), free(argv[2]), fd);
}

void	here_doc(int argc, char **argv, char **envp)
{
	int			infile;
	int			outfile;
	int			i;
	int			executed;

	i = 0;
	executed = 0;
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
	if (outfile == -1)
		hexit ("/tmp/tmp.tmp", "Failed to open outfile\n", 1);
	if (call_command_to_fd(infile, outfile, argv[i], envp) != -1)
		executed ++;
	hexit ("/tmp/tmp.tmp", NULL, 1);
}
