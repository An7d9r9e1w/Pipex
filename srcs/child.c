#include <pipex.h>

void	try_exec(char *arg, int	*fildes, int out, char **paths)
{
	char	**args;

	args = get_args(arg, paths);
	if (!args)
		error_fds(1, arg, fildes, out);
	if (fildes[1] > 2)
	{
		close(fildes[1]);
		fildes[1] = 0;
	}
	if (dup2(fildes[0], 0) == -1 || dup2(out, 1) == -1
		|| execve(*args, args, 0) == -1)
	{
		free_strs(args);
		error_fds(1, arg, fildes, out);
	}
}

void	last_child(char **argv, int out, char **paths)
{
	int	fildes[2];

	default_fds(fildes);
	*fildes = open(*argv, O_RDONLY);
	if (*fildes == -1)
		error_fds(1, *argv, fildes, out);
	try_exec(argv[1], fildes, out, paths);
}

void	first_child(int argc, char **argv, int out, char **paths)
{
	int	fildes[2];
	int	pid;

	if (out == -1)
		error_fds(1, argv[argc], fildes, out);
	default_fds(fildes);
	if (pipe(fildes) == -1)
		error(1, argv[argc]);
	pid = fork();
	if (pid == -1)
		error_fds(1, argv[argc], fildes, 0);
	if (pid)
		try_exec(argv[argc - 1], fildes, out, paths);
	else
	{
		close(fildes[0]);
		last_child(argv, fildes[1], paths);
	}
}
