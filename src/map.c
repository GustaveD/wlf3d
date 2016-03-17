/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:27:12 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/17 13:38:19 by jrosamon         ###   ########.fr       */
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
			j++;
		}
		i++;
		printf("boucle\n");
	}
	if (err == -1)
	{
		printf("err = %d\n", err);
		return (0);
	}
	return (1);
}

int			ft_create_map(t_env *e, int fd)
{
	int i;

	printf("entrer create_map\n");
	i = 0;
	if (fd == -1)
		return (0);
	if (!(e->map = (int**)malloc(sizeof(int*) * map_width)))
		return (0);
	while (i < map_width)
	{
		if (!(e->map[i] = (int*)malloc(sizeof(int) * map_width)))
			return (0);
		i++;
	}
	printf("e->map[i] = %d\n", &e->map[i]);
	printf("malloc map ok\n");
	if (!(ft_map(e, fd)))
	{
		printf("ft_map mort\n");
		return (0);
	}
	return (1);
}
