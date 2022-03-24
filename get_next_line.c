/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojeong <hyojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 22:14:21 by hyojeong          #+#    #+#             */
/*   Updated: 2022/03/23 19:31:44 by hyojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

/* 임시___반드시 지울 것 */
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
#endif

// 메모리 관리 엄청 신경쓸 것!!!! 
char	*check_newline(char *buffer, char **tmp, char *line, char *flag)
{
	size_t	idx;

	idx = 0;
	while (buffer[idx])
	{
		if (buffer[idx] == '\n')
			break;
		idx++;
	}
	if (idx == BUFFER_SIZE)
	{
		line = ft_strjoin(line, buffer);
		ft_bzero(buffer, BUFFER_SIZE);
	}
	else
	{
		*tmp = buffer + (idx + 1);
		ft_strlcat(line, buffer, (ft_strlen(line) + idx + 2));
		*flag = 0;
	}
	return (line);
}

char	*check_tmp(char **tmp, char *line, char *flag)
{
	size_t	idx;

	idx = 0;
	while ((*tmp)[idx])
	{
		if ((*tmp)[idx] == '\n')
			break;
		idx++;
	}
	if ((*tmp)[idx] == '\0')
	{
		line = ft_strjoin(line, *tmp);
		*flag = 0;
	}
	else
	{
		ft_strlcat(line, *tmp, (ft_strlen(line) + idx + 2));
		*tmp = *tmp + (idx + 1);
		*flag = 2;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*tmp;
	char		*line;
	char		flag;

	flag = 1;
	if (tmp == 0)
		tmp = (char *)ft_calloc(1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	line = ft_calloc(1, sizeof(char));
	if (buffer == 0 || line == 0 || fd < 0)
		return (0);
	while (flag) // if 문으로 변환, free 처음부터 꼭 넣어서 짜보자.
	{
		line = check_tmp(&tmp, line, &flag);
		if (flag == 2)
		{
			return (line);
		}
	}
	flag = 1;
	while (flag)
	{
		if (read(fd, buffer, BUFFER_SIZE) == -1) // 읽기 실패 했을때 모든 메모리 할당헤재
		{
			return (0);
		}
		line = check_newline(buffer, &tmp, line, &flag);
	}
	return (line); // 마지막 널을 반환하기 직전에 buffer랑 line을 할당해제해야함
}
