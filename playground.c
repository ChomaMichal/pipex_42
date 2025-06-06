#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
int main(int argc, char **av, char **env)
{
	char *args[] = {"/run/current-system/sw/bin/bash", "-c",  "cat file1", NULL};
	int		fd[2];
	int		tmp;
	pid_t f;
	char str[80];
	char *program = "/run/current-system/sw/bin/bash";
	char *command = "echo hello";
	char *envp[] = {NULL};

	fd[0] = 10;
	fd[1] = 20;
	pipe(fd);
	f =fork();
	if (0 == f)
	{
	dup2(fd[1], 1);
		printf("%i\n", execve(program, args, env));
	}
	else 
	{
		waitpid(1, &f, 0);
		read(fd[0], str, 9);
		str[9] = 0;
		printf("parent %s\n", str);
	}
	return 1;
}
