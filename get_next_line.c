/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojeong <hyojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 22:14:21 by hyojeong          #+#    #+#             */
/*   Updated: 2022/03/28 09:37:09 by hyojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

/* 임시___반드시 지울 것 */
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

ssize_t	is_newline(char *str)
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

char	*ft_read(char *tmp, int fd)
{
	char	*buffer;
	int		read_tmp;

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
		{
			// free(tmp);
			break;
		}
		tmp = ft_strjoin(tmp, buffer);
		if (is_newline(buffer) != -1)
			break ;
		ft_bzero(buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (tmp);
}

char	*split(char *tmp)
{
	ssize_t	idx;
	char	*buffer;

	idx = is_newline(tmp);
	if (idx == -1)
		idx = ft_strlen(tmp);
	buffer = ft_calloc(idx + 1, sizeof(char));
	ft_strlcat(buffer, tmp, idx + 2); //의심
	return (buffer);
}

char	*remain_tmp(char *tmp)
{
	ssize_t	idx;
	char	*new_str;

	idx = is_newline(tmp);
	if (idx == -1)
		return (0);
	new_str = ft_calloc(ft_strlen(tmp) - idx, sizeof(char));
	ft_strlcat(new_str, tmp + idx + 1, ft_strlen(tmp) - idx);
	free(tmp);
	return (new_str);
}

// 메모리 관리 엄청 신경쓸 것!!
char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buffer;

	if (is_newline(tmp) != -1)
	{
		buffer = split(tmp);
		tmp = remain_tmp(tmp);
		return (buffer);
	}
	if (tmp)
		tmp = ft_strjoin(tmp, ft_read(tmp, fd));
	else
		tmp = ft_read(tmp, fd);
	buffer = split(tmp);
	if (tmp == 0)
	{
		free(tmp);
		free(buffer);
		return (0);
	}
	tmp = remain_tmp(tmp);
	if (buffer[0] == '\0')
		return (0);
	return (buffer);
}

// 41_no_nl : -----01 (추가로 버퍼 2개가 더 출력되는 문제점)