/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <jrosamon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 18:04:33 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/23 23:39:55 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "wolf.h"
#include <stdio.h>

static int			ft_err(char **save)
{
	if (*save)
		ft_strdel(save);
	return (-1);
}

static void			ft_ret(char **line, char **save)
{
	size_t			len;
	char			*tmp;

	tmp = *save;
	len = ft_strchr(*save, '\n') - *save;
	*line = ft_strsub(tmp, 0, len);
	*save = ft_strdup(tmp + len + 1);
	if ((*save) == NULL)
		ft_strdel(save);
	free(tmp);
}

static int			ft_end(char **line, char **save)
{
	if (ft_strlen(*save) != 0)
	{
		*line = ft_strdup(*save);
		ft_strclr(*save);
		return (1);
	}
	*line = ft_strdup(*save);
	ft_strdel(save);
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*save = NULL;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	ret = 0;
	if (fd == -1 || BUFF_SIZE <= 0)
		return (ft_err(&save));
	if (save == NULL)
		save = ft_strnew(BUFF_SIZE + 1);
	ret = read(fd, buff, BUFF_SIZE);
	while (save != NULL && ft_strchr(save, '\n') == NULL
			&& ((ret = read(fd, buff, BUFF_SIZE)) > 0))
	{
		buff[ret] = '\0';
		tmp = save;
		save = ft_strjoin(tmp, buff);
		free(tmp);
	}
	if (ret == -1)
		return (-1);
	if (ret == 0 && ft_strchr(save, '\n') == NULL)
		return ((ft_end(line, &save)));
	ft_ret(line, &(save));
	return (1);
}
