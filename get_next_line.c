/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojeong <hyojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 22:14:21 by hyojeong          #+#    #+#             */
/*   Updated: 2022/03/21 11:51:41 by hyojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h>
#include <limits.h>

static	int	is_new_end_line(char *str)
{
	while ((str == '\n') || (str == '\0'))
	{

	}
}

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	static	??

	while ()
}