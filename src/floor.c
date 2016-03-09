/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 16:30:02 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/09 18:01:52 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_direction_floor(t_env *e)
{
	if (e->rc->side == 0 && e->rc->rayDirX > 0)
	{
		e->fl->fxwall = e->rc->mapX;
		e->fl->fywall = e->rc->mapY + e->rc->wallX;
	}
	else if (e->rc->side == 0 && e->rc->rayDirX < 0)
	{
		e->fl->fxwall = e->rc->mapX + 1.0;
		e->fl->fywall = e->rc->mapY + e->rc->wallX;
	}
	else if (e->rc->side == 1 && e->rc->rayDirY < 0)
	{
		e->fl->fxwall = e->rc->mapX + e->rc->wallX;
		e->fl->fywall = e->rc->mapY;
	}
	else
	{
		e->fl->fxwall = e->rc->mapX + e->rc->wallX;
		e->fl->fywall = e->rc->mapY + 1.0;
	}
	ft_draw_floor(e);
}

void	ft_floor_to_img(t_env *e, int x, int y)
{
	int i;
	int tmp;

	i = x * 4 + y * e->isizeline;
	tmp = e->fl->ftextx * (e->texture[5]->bpp / 8) + e->fl->ftexty 
			* e->texture[5]->sizeline;
	e->idata[i] = e->texture[5]->data[tmp];
	e->idata[i + 1] = e->texture[5]->data[tmp + 1];
	e->idata[i + 2] = e->texture[5]->data[tmp + 2];
	e->idata[i + 3] = 1;
}

void	ft_draw_floor(t_env *e)
{
	int i;

	i = e->rc->drawEnd + 1;
	e->fl->distwall = e->rc->perpWallDist;
	e->fl->distplayer = 0;
	if (e->rc->drawEnd < 0)
		e->rc->drawEnd = WIN_HEIGHT;
	while (i < WIN_HEIGHT)
	{
		e->fl->currdist = WIN_HEIGHT/ ( 2.0 * i - WIN_HEIGHT);
		e->fl->weight = (e->fl->currdist - e->fl->distplayer) /
							(e->fl->distwall - e->fl->distplayer);
		e->fl->currfloorx = e->fl->weight * e->fl->fxwall + (1.0 - e->fl->weight) * PPOSX;
		e->fl->currfloory = e->fl->weight * e->fl->fywall + (1.0 - e->fl->weight) * PPOSY;
		e->fl->ftextx = (int)(e->fl->currfloorx * TEXT_WIDTH) % TEXT_WIDTH;
		e->fl->ftexty = (int)(e->fl->currfloory * TEXT_HEIGHT) % TEXT_HEIGHT;
		ft_floor_to_img(e, e->rc->x, i);
		i++;
	}

}
