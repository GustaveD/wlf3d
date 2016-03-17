/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:48 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/17 13:38:22 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
int			ft_error(int er)
{
	if (er == 0)
		write (1, "ERROR: Put a map\n", ft_strlen("ERROR: Put a map\n"));
	if (er == 1)
		write (1, "ERROR: init Map\n", ft_strlen("ERROR: init Map\n"));
	if (er == 2)
		write (1, "ERROR: init player\n", ft_strlen("ERROR: init player\n"));
	if (er == 3)
		write (1, "ERROR: init texture\n", ft_strlen("ERROR: init texture\n"));
	if (er == 4)
		write (1, "ERROR: init Raycaststruct\n", ft_strlen("ERROR: init Raycaststruct\n"));	
	return (er);
}*/

/*static void		destroy_text(e)
{
	(void)e;
}*/

static void		destroy_map(int **map)
{
	int		i;
	int		j;

	printf("destroy_map enter\n");
	i = 0;
	while (i < 24)
	{
		j = 0;
		while (j < 24)
		{
			free(&map[i]);
			j++;
		}
		i++;
	}
}

void			ft_error(int err, t_env *e, char *s)
{
	if (e)
	{
		e->img != NULL ? mlx_destroy_image(e->mlx, e->img) : 0;
		e->win != NULL ? mlx_destroy_window(e->mlx, e->win) : 0;
		e->map != NULL ? destroy_map(e->map) : 0;
	}
	if (s)
		ft_putstr_fd(s, err);
	exit (0);
}
