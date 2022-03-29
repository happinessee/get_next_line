/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojeong <hyojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 22:14:21 by hyojeong          #+#    #+#             */
/*   Updated: 2022/03/29 13:18:52 by hyojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h>
#include <stdlib.h>

static ssize_t	is_newline(char *str)
{
	ssize_t	idx;

	idx = 0;
	if (str == 0)
		return (-1);
	while (str[idx])
	{
		if (str[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

static char	*ft_read(int fd)
{
	char	*buffer;
	int		read_tmp;
	char	*tmp;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_tmp = 0;
	while (1)
	{
		read_tmp = read(fd, buffer, BUFFER_SIZE);
		if (read_tmp < 0)
		{
			free(buffer);
			free(tmp);
			return (0);
		}
		if (read_tmp == 0)
			break ;
		tmp = ft_strjoin(tmp, buffer, 2);
		if (is_newline(buffer) != -1)
			break ;
		ft_bzero(buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (tmp);
}

static char	*split(char *tmp)
{
	ssize_t	idx;
	char	*buffer;

	if (tmp == 0)
		return (0);
	idx = is_newline(tmp);
	if (idx == -1)
		idx = ft_strlen(tmp);
	buffer = ft_calloc(idx + 2, sizeof(char));
	ft_strlcat(buffer, tmp, idx + 2);
	return (buffer);
}

static char	*remain_tmp(char *tmp)
{
	ssize_t	idx;
	char	*new_str;

	idx = is_newline(tmp);
	if (idx == -1)
	{
		free(tmp);
		return (0);
	}
	new_str = ft_calloc(ft_strlen(tmp) - idx, sizeof(char));
	ft_strlcat(new_str, tmp + idx + 1, ft_strlen(tmp) - idx);
	free(tmp);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (is_newline(tmp) != -1)
	{
		buffer = split(tmp);
		tmp = remain_tmp(tmp);
		return (buffer);
	}
	tmp = ft_strjoin(tmp, ft_read(fd), 1);
	if (tmp == 0)
		return (0);
	if (tmp[0] == '\0')
	{
		free(tmp);
		tmp = 0;
		return (0);
	}
	buffer = split(tmp);
	tmp = remain_tmp(tmp);
	return (buffer);
}
