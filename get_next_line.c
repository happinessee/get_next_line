/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojeong <hyojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 22:14:21 by hyojeong          #+#    #+#             */
/*   Updated: 2022/03/22 14:07:41 by hyojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h>
#include <limits.h>

/* 임시___반드시 지울 것 */
#define BUFFER_SIZE 4

static void	make_line(char *new_str, char *buffer, char *buffer2, char *flag)
{
	size_t	idx;

	idx = 0;
	while (buffer[idx])
	{
		if (buffer[idx] == '\n')
			break ;
		idx++;
	}
	if (idx == BUFFER_SIZE)
		ft_strlcat(new_str, buffer, ft_strlen(new_str) + BUFFER_SIZE + 1);
	else
	{
		ft_strlcat(new_str, buffer, ft_strlen(new_str) + idx + 1);
		ft_strlcat(buffer2, buffer + (idx + 1), BUFFER_SIZE);
		*flag = 0;
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	buffer2[BUFFER_SIZE + 1];
	char		*line;
	char		flag;

	flag = 1;
	line = ft_calloc(1, 4096);
	buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if ((fd < 0) || BUFFER_SIZE <= 0 || buffer == 0)
		return (0);
	if (buffer2[0] != '\0')
	{
		ft_strlcat(line, buffer2, ft_strlen(buffer2) + 1);
		ft_bzero(buffer2, (BUFFER_SIZE + 1));
	}
	while (flag)
	{
		if (read(fd, buffer, BUFFER_SIZE) == -1)
			return (0);
		make_line(line, buffer, buffer2, &flag);
		ft_bzero(buffer, BUFFER_SIZE + 1);
	}
	return (line);
}