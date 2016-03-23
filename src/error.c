/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:48 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/23 13:24:47 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		ft_free_map(t_env *e)
{
	int i;
	int j;

	i = 0;
	while (i < 24)
	{
		j = 0;
		while (j < 24)
		{
			free(&(e->map[i][j]));
			j++;
		}
		i++;
	}
}

static void		ft_free_player(t_env *e)
{
	free(&(e->p->pos));
	free(&(e->p->dir));
	free(&(e->p->plane));
	free(&(e->p));
}

void			ft_error(int err, t_env *e, char *s)
{
	if (e)
	{
		e->img != NULL ?
			mlx_destroy_image(e->mlx, e->img) : 0;
		e->win != NULL ?
			mlx_destroy_window(e->mlx, e->win) : 0;
		e->map != NULL ?
			ft_free_map(e) : 0;
		e->p != NULL ?
			ft_free_player(e) : 0;
	}
	if (s)
		ft_putstr_fd(s, err);
	exit(0);
}
