/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:04:57 by mchoma            #+#    #+#             */
/*   Updated: 2025/06/09 16:04:58 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
# include <stdint.h>
# include <fcntl.h>
# include "printf.h"
# include "libft.h"

typedef struct s_command
{
	char	*bin;
	char	**args;
}	t_command;

int			permitions(char *read, char *write);
int			piped_child(int outfile, int infile, int lose, t_command *command);
char		*get_path(char**envp, char *command);
t_command	*fill_command(char *args, char **envp);
void		free_split(char ***split);
void		free_command(t_command **command);

#endif
