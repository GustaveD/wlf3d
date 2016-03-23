/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:11:41 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/23 19:02:03 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				draw(t_env *e)
{
	fill_img(e, 0);
	ft_raycasting(e);
	e->oldtime = e->time;
	e->time = clock();
	e->frametime = (e->time - e->oldtime) / 1000.0;
	if (!e->key->run)
		PMOVS = e->frametime / 200;
	else
		PMOVS = e->frametime / 150;
	PROTS = e->frametime / 500;
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	draw_weapon(e);
	return (0);
}
