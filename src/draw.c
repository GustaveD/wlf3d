/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:11:41 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/18 11:51:01 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		draw(t_env *e)
{
	fill_img(e, 200);
	ft_raycasting(e);
	e->oldtime = e->time;
	e->time = clock();
	e->frametime = (e->time - e->oldtime) / 1000.0;
	PMOVS = e->frametime / 20;
	PROTS = e->frametime / 50;
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_put_image_to_window(e->mlx, e->win, e->gun->img->i, e->gun->x, e->gun->y);
	return (0);
}
