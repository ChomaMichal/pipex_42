
// outputfd  if where shit should be writen
// filefd is where we get shit from
// command says what should we do with it
int	piped_child(int fd, char *file, char* command)
{
	char	*program;
	char	*args[];
	char	*env[];
	int		f;

	program = "/run/current-system/sw/bin/bash";
	args = {"/run/current-system/sw/bin/bash", "-c",  command, NULL};
	env = {NULL};
	f = fork();
	if (f == 0)
	{
		if (execve(program, args, env) == -1)
		{
			close(fd);
			return (-1);
		}
		return (-1);
	}
	waitpid(1, &f, 0);
	return (1);
}

