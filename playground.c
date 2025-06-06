#include <unistd.h>
#include <stdio.h>
#include <errno.h>
int main(int argc, char **av, char **env)
{
	char *args[] = {"/run/current-system/sw/bin/ls", NULL, NULL};
	int		fd[2];
	pid_t f;
	char str[80];
	char *program = "/run/current-system/sw/bin/ls";
	char *command = "echo hello";
	char *envp[] = {NULL};

	fd[0] = 10;
	fd[1] = 20;
	// pipe(fd);
	f =fork();
	if (0 == f)
	{
	//	write(fd[1], "HI DADDY", 9);
		printf("%i\n", execve(program, args, env));
		execve("/run/current-system/sw/bin/ls", args, NULL);
		printf("hehehehhe %i\n", errno);
	}
	else 
	{
		
		read(fd[0], str, 9);
		str[9] = 0;
		printf("parent %s\n", str);
	}
	return 1;
}
