/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:27:12 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/14 11:29:00 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		ft_map(t_env *e, int fd)
{
	int		i;
	int		j;
	char	*line;
	char	**lines;

	line = NULL;
	i = 0;
	while (get_next_line(fd, &line))
	{
		lines = ft_strsplit(line, ' ');
		j = 0;
		while (lines[j] != NULL)
		{
			e->map[i][j] = ft_atoi(lines[j]);
			j++;
		}
		i++;
	}
}

void		ft_create_map(t_env *e, int fd)
{
	int i;

	i = 0;
	if (!(e->map = (int**)malloc(sizeof(int*) * map_width)))
		exit(EXIT_FAILURE);
	while (i < map_width)
	{
		if (!(e->map[i] = (int*)malloc(sizeof(int) * map_width)))
			exit(EXIT_FAILURE);
		i++;
	}
	ft_map(e, fd);
}
