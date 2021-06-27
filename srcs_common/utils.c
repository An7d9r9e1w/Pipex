#include <pipex.h>

char	**get_paths(char *envp[])
{
	char	**paths;

	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		error(0, "No PATH environment variable");
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		error(1, "Env");
	return (paths);
}

int	search_path(char **file, char **paths)
{
	char	buf[256];
	char	*path;
	int		fd;
	int		i;

	fd = -1;
	while (fd == -1 && *paths)
	{
		i = ft_strlcpy(buf, *paths++, 256);
		buf[i++] = '/';
		ft_strlcpy(buf + i, *file, 256 - i);
		fd = open(buf, O_RDONLY);
	}
	if (fd == -1)
		return (-1);
	path = ft_strdup(buf);
	if (!path)
		return (-1);
	free(*file);
	*file = path;
	return (0);
}

char	**get_args(char *arg, char **paths)
{
	char	**args;
	char	cmd[256];
	int		i;

	args = ft_split(arg, ' ');
	if (!args)
		return (0);
	if (search_path(args, paths) == -1)
	{
		i = ft_strlcpy(cmd, "pipex: command not found: ", 256);
		ft_strlcpy(cmd + i, *args, 256 - i);
		free_strs(args);
		error(0, cmd);
	}
	return (args);
}

void	default_fds(int *fildes)
{
	fildes[0] = 0;
	fildes[1] = 0;
}
