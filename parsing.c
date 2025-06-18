

#include "pipex.h"
#include "printf.h"
#include "stdio.h"

void	printstrarr(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
	{
		printf("%s\n", arr[i]);
		i ++;
	}
}

char	*isbin(char *path, char *command)
{
	char	*binpath;
	char	*tmp;

	tmp = ft_strjoin("/", command);
	if (!tmp)
		return (NULL);
	binpath = ft_strjoin(path, tmp);
	free(tmp);
	if (binpath)
	{
		if (access(binpath, X_OK) == 0)
			return (binpath);
	}
	free(binpath);
	return (NULL);
}

char	**get_fc(char *rawcommand)
{
	return(ft_split(rawcommand,' '));
}

void	free_split(char ***split)
{
	int		i;
	
	i = 0;
	while((*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
	*split = NULL;
}

char	*get_path(char**envp, char *command)
{
	int i;
	int j;
	char	**arr;
	char	*path;

	arr = NULL;
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
					return (free_split(&arr),path);
				j++;
			}
		}
		i ++;
	}
	return (free_split(&arr), NULL);
}
