#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

void	free_strs(char **strs);
void	close_fds(int *fildes, int out);
void	error(int stderror, char *msg);
void	error_fds(int stderror, char *msg, int *fildes, int out);

char	**get_paths(char *envp[]);
int		search_path(char **file, char **paths);
char	**get_args(char *arg, char **paths);
void	default_fds(int *fildes);

void	heredoc(char *limiter, int out);
void	try_exec(char *arg, int	*fildes, int out, char **paths);
void	last_child(char **argv, int out, char **paths);
void	next_child(int argc, char **argv, int out, char **paths);
void	first_child(int argc, char **argv, int out, char **paths);

#endif	/*PIPEX_H*/
