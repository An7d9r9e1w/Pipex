#include <pipex.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	**paths;
	int		pid;
	int		stat_loc;
	int		hdflag;

	hdflag = argc > 1 && !ft_strncmp(argv[1], "here_doc", 9);
	if (hdflag && argc < 6)
		error(0, "Format: here_doc LIMITER cmd1 cmd2 ... cmdn file2");
	if (!hdflag && argc < 5)
		error(0, "Format: file1 cmd1 cmd2 cmd3 ... cmdn file2");
	paths = get_paths(envp);
	pid = fork();
	if (pid == -1)
	{
		free_strs(paths);
		error(1, "Main");
	}
	stat_loc = 0;
	hdflag = O_WRONLY | O_CREAT | hdflag * O_APPEND | !hdflag * O_TRUNC;
	if (!pid)
		first_child(argc - 2, argv + 1,
			open(argv[argc - 1], hdflag, 0755), paths);
	waitpid(pid, &stat_loc, 0);
	free_strs(paths);
	return (stat_loc);
}
