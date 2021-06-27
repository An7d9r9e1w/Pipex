#include <pipex.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	**paths;
	int		pid;
	int		stat_loc;

	if (argc != 5)
		error(0, "Format: file1 cmd1 cmd2 file2");
	paths = get_paths(envp);
	pid = fork();
	if (pid == -1)
	{
		free_strs(paths);
		error(1, "Main");
	}
	stat_loc = 0;
	if (!pid)
		first_child(argc - 2, argv + 1,
			open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0755), paths);
	waitpid(pid, &stat_loc, 0);
	free_strs(paths);
	return (stat_loc);
}
