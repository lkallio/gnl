/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:36:18 by lkallio           #+#    #+#             */
/*   Updated: 2019/11/15 15:18:46 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_join(char **line, char *portion)
{
	char	*temp;
	int		ret;

	if (!*line)
		if (!(*line = ft_strnew(0)))
			return (-1);
	temp = *line;
	ret = ft_strcjoin(line, portion, '\n', 0);
	free(temp);
	return (ret);
}

int			get_next_line(const int fd, char **line)
{
	static char		buf[HANDLE_MAX][BUFF_SIZE + 1];
	int				ret;

	if (!line || fd < 0 || fd > HANDLE_MAX - 1)
		return (-1);
	*line = 0;
	ret = BUFF_SIZE;
	while (buf[fd][0] || (ret = read(fd, buf[fd], BUFF_SIZE)) > 0)
	{
		buf[fd][ret] = 0;
		if ((ret = gnl_join(line, buf[fd])))
		{
			ft_strcpy(buf[fd], ft_strchr(buf[fd], '\n') + 1);
			return (ret);
		}
		buf[fd][0] = 0;
	}
	return (ret < 0 ? ret : !!*line);
}
