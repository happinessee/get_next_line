/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojeong <hyojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 22:14:26 by hyojeong          #+#    #+#             */
/*   Updated: 2022/03/28 17:17:46 by hyojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>

size_t	ft_strlen(char *str)
{
	size_t	cnt;

	cnt = 0;
	if (str == 0)
		return (0);
	while (str[cnt])
		cnt++;
	return (cnt);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			cnt;
	unsigned char	*str;

	if (n == 0)
		return ;
	str = (unsigned char *)s;
	cnt = 0;
	while (cnt < n)
	{
		str[cnt] = '\0';
		cnt++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*mem;
	size_t			idx;

	idx = 0;
	mem = malloc(size * count);
	if (mem == 0)
		return (0);
	while (idx < size * count)
	{
		mem[idx] = 0;
		idx++;
	}
	return (mem);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	dst_len;
	size_t	src_len;

	index = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	if (dst == 0 || src == 0)
		return (0);
	while (src[index] && dst_len + index + 1 < dstsize)
	{
		dst[dst_len + index] = src[index];
		index++;
	}
	dst[dst_len + index] = 0;
	return (dst_len + src_len);
}

char	*ft_strjoin(char *s1, char *s2, int flag)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = ft_calloc(len, sizeof(char));
	if (str == 0)
		return (0);
	ft_strlcat(str, s1, len);
	ft_strlcat(str, s2, len);
	if (s1 && flag == 1)
		free (s1);
	if (s2 && flag == 1)
		free (s2);
	if (flag == 2)
		free (s1);
	return (str);
}
