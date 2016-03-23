/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:27:12 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/23 23:39:54 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			ft_map(t_env *e, int fd)
{
	int		i;
	int		j;
	char	*line;
	char	**lines;
	int		err;

	line = NULL;
	i = 0;
	while ((err = (get_next_line(fd, &line))) > 0)
	{
		lines = ft_strsplit(line, ' ');
		j = 0;
		while (lines[j] != NULL)
		{
			e->map[i][j] = ft_atoi(lines[j]);
			free(lines[j]);
			j++;
		}
		i++;
		free(lines);
		free(line);
	}
	if (err == -1)
		return (0);
	return (1);
}

int			ft_create_map(t_env *e, int fd)
{
	int i;

	i = 0;
	if (fd == -1)
	{
		printf("fini\n");
		return (0);
	}
	if (!(e->map = (int**)malloc(sizeof(int*) * 24)))
		return (0);
	while (i < 24)
	{
		if (!(e->map[i] = (int*)malloc(sizeof(int) * 24)))
			return (0);
		i++;
	}
	if (!(ft_map(e, fd)))
		return (0);
	return (1);
}
