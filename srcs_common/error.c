#include <pipex.h>

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	close_fds(int *fildes, int out)
{
	if (fildes)
	{
		if (fildes[0] > 2)
			close(fildes[0]);
		if (fildes[1] > 2)
			close(fildes[1]);
	}
	if (out > 2)
		close(out);
}

void	error(int stderror, char *msg)
{
	if (stderror)
		perror(msg);
	else
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	exit(1);
}

void	error_fds(int stderror, char *msg, int *fildes, int out)
{
	close_fds(fildes, out);
	error(stderror, msg);
}
