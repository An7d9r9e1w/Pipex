/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 20:05:06 by nnamor            #+#    #+#             */
/*   Updated: 2021/04/30 20:10:05 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *str);
char	*cat(char *dst, const char *src, size_t len);
int		init_buf(char **buf, size_t *len);
void	free_buf(char **buf);

static int	parse_linefeed(char *buf, size_t *len, char **line)
{
	size_t	i;
	ssize_t	j;
	ssize_t	cnt;
	char	lf;

	i = 0;
	while (i < *len && buf[i] != '\n')
		i++;
	lf = i != *len && buf[i] == '\n';
	*line = cat(*line, buf, i);
	if (!*line)
		return (-1);
	cnt = *len - i - 1;
	j = -1;
	while (++j < cnt)
		buf[j] = buf[++i];
	*len = j;
	return (lf);
}

int	get_next_line(int fd, char **line)
{
	static char		*buf = 0;
	static size_t	len = 0;
	ssize_t			cnt;
	int				lf;

	if (!line || (!buf && init_buf(&buf, &len)))
		return (-1);
	*line = 0;
	lf = 0;
	cnt = 1;
	while (!lf && cnt)
	{
		cnt = read(fd, buf + len, BUFFER_SIZE - len);
		if (cnt < 0)
			break ;
		len += cnt;
		lf = parse_linefeed(buf, &len, line);
	}
	if (cnt < 0)
		lf = cnt;
	if (lf < 0 || (!len && !cnt))
		free_buf(&buf);
	if (lf < 0 && *line)
		free_buf(line);
	return (lf);
}
