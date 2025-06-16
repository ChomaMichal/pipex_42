

#include "pipex.h"
#include "printf.h"

void	printstrarr(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i ++;
	}
}

char	*isbin(char *path, char *command)
{
	char	*binpath;
	binpath  = ft_strjoin("/", command);
	if (binpath)
		binpath = ft_strjoin(path, binpath);
	if (binpath)
	{
		if (access(binpath, X_OK) == 0)
			return (binpath);
	}
	return (NULL);
}

char	**get_fc(char *rawcommand)
{
	return(ft_split(rawcommand,' '));
}



char	*get_path(char**envp, char *command)
{
	int i;
	int j;
	char	**arr;
	char	*path;

	i = 0;
	while(envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			arr = ft_split(envp[i] + 5, ':');
			//printstrarr(arr);
			j = 0;
			while(arr[j])
			{
				path = isbin(arr[j], command);
				if(path)
					return (path);
				j++;
			}
		}
		i ++;
	}
	return (NULL);
}
