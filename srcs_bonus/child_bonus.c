#include <pipex.h>
#include <get_next_line.h>

void	heredoc(char *limiter, int out)
{
	char	*line;
	int		lf;

	if (write(0, "pipe heredoc> ", 14) == -1)
		error_fds(1, "heredoc", 0, out);
	lf = get_next_line(0, &line);
	if (lf == -1)
		error_fds(1, "stdin", 0, out);
	while (lf > -1 && ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
	{
		if (lf > 0 && (write(out, line, ft_strlen(line)) == -1
				|| write(out, "\n", 1) == -1
				|| write(0, "pipe heredoc> ", 14) == -1))
			break ;
		free(line);
		lf = get_next_line(0, &line);
	}
	free(line);
	close(out);
	if (lf == -1)
		error(1, "heredoc");
}

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

	if (ft_strncmp(*argv, "here_doc", 9))
	{
		default_fds(fildes);
		*fildes = open(*argv, O_RDONLY);
		if (*fildes == -1)
			error_fds(1, *argv, fildes, out);
		try_exec(argv[1], fildes, out, paths);
	}
	else
		heredoc(argv[1], out);
}

void	next_child(int argc, char **argv, int out, char **paths)
{
	int	fildes[2];
	int	pid;

	while (argc > 1)
	{
		default_fds(fildes);
		if (pipe(fildes) == -1)
			error_fds(1, argv[argc], fildes, out);
		pid = fork();
		if (pid == -1)
			error_fds(1, argv[argc], fildes, out);
		if (pid)
			try_exec(argv[argc], fildes, out, paths);
		else
		{
			close(fildes[0]);
			close(out);
			out = fildes[1];
			argc--;
		}
	}
	last_child(argv, out, paths);
}

void	first_child(int argc, char **argv, int out, char **paths)
{
	int	fildes[2];
	int	pid;

	if (out == -1)
		error(1, argv[argc]);
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
		next_child(argc - 2, argv, fildes[1], paths);
	}
}
