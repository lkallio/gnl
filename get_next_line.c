/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:07:20 by lkallio           #+#    #+#             */
/*   Updated: 2019/11/08 12:37:16 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "get_next_line.h"

static int	find_newline(char *portion, int i, int n)
{
	if (!n)
		return (-1);
	if (*portion == '\n' || !*portion)
		return (i);
	return (find_newline(portion + 1, i + 1, n - 1));
}

static char	*gnl_join(char **buf_temp, char *portion, int n)
{
	char	*out;

	if (!buf_temp)
		return (ft_strdup(portion));
	out = ft_strnjoin(*buf_temp, portion, n);
	free(*buf_temp);
	return (out);
}

int			get_next_line(const int fd, char **line)
{
	static char		buf[HANDLE_MAX][BUFF_SIZE + 1];
	char			*buf_temp;
	int				ret;
	int				newline;

	if (fd < 0 || !(buf_temp = gnl_join(0, buf[fd], 0)))
		return (-1);
	while ((ret = read(fd, buf[fd], BUFF_SIZE)) > 0)
	{
		if ((newline = find_newline(buf[fd], 0, BUFF_SIZE)) > -1)
		{
			*line = gnl_join(&buf_temp, buf[fd], newline);
			ft_strncpy(buf[fd], buf[fd] + newline + 1,
					ft_strlen(buf[fd]));
			return (*line ? 1 : -1);
		}
		if (!(buf_temp = gnl_join(&buf_temp, buf[fd], BUFF_SIZE)))
			return (-1);
		buf[fd][0] = 0;
	}
	return (ret);
}
