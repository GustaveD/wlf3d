/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:48 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/23 23:17:19 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		ft_free_map(t_env *e)
{
	int i;

	i = 0;
	while (++i < 24)
		free(e->map[i]);
	free(e->map);
}

static void		ft_free_player(t_env *e)
{
	free(e->p->pos);
	free(e->p->dir);
	free(e->p->plane);
	free((e->p));
}

static void		ft_free_rc(t_env *e)
{
	free(RC);
	FL != NULL ? free(FL) : 0;
	e->gun != NULL ? free(e->gun) : 0;
	e->key != NULL ? free(e->key) : 0;
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
		RC != NULL ?
			ft_free_rc(e) : 0;
	}
	if (s)
		ft_putstr_fd(s, err);
	exit(0);
}
