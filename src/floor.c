/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 16:30:02 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/23 12:43:33 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				ft_create_floor(t_env *e)
{
	if (!(FL = (t_floor*)malloc(sizeof(t_floor))))
		return (0);
	ft_bzero(FL, sizeof(t_floor));
	return (1);
}

void			ft_direction_floor(t_env *e)
{
	if (RC->side == 0 && RC->ray_dirx > 0)
	{
		FL->fxwall = RC->mapx;
		FL->fywall = RC->mapy + RC->wall_x;
	}
	else if (RC->side == 0 && RC->ray_dirx < 0)
	{
		FL->fxwall = RC->mapx + 1.0;
		FL->fywall = RC->mapy + RC->wall_x;
	}
	else if (RC->side == 1 && RC->ray_diry > 0)
	{
		FL->fxwall = RC->mapx + RC->wall_x;
		FL->fywall = RC->mapy;
	}
	else
	{
		FL->fxwall = RC->mapx + RC->wall_x;
		FL->fywall = RC->mapy + 1.0;
	}
	ft_draw_floor(e);
}

void static		ft_draw_sky(t_env *e, int y)
{
	int color;

	FL->ftextx = (int)(FL->currfloorx * TEXT[4]->wdth) % TEXT[4]->wdth;
	FL->ftexty = (int)(FL->currfloory * TEXT[4]->hght) % TEXT[4]->hght;
	color = *((unsigned int*)(TEXT[4]->data +
				(TEXT[4]->wdth * FL->ftexty * 4 + FL->ftextx * 4)));
	img_put_pixel(e, RC->x, WIN_HEIGHT - y, color);
}

void			ft_draw_floor(t_env *e)
{
	int i;
	int color;

	i = RC->draw_end + 1;
	FL->distwall = RC->perp_wall_d;
	FL->distplayer = 0.0;
	if (RC->draw_end < 0)
		RC->draw_end = WIN_HEIGHT;
	while (++i < WIN_HEIGHT)
	{
		FL->currdist = WIN_HEIGHT / (2.0 * i - WIN_HEIGHT);
		FL->weight = (FL->currdist - FL->distplayer) /
							(FL->distwall - FL->distplayer);
		FL->currfloorx = FL->weight * FL->fxwall + (1.0 - FL->weight) * PPOSX;
		FL->currfloory = FL->weight * FL->fywall + (1.0 - FL->weight) * PPOSY;
		FL->ftextx = (int)(FL->currfloorx * TEXT[5]->wdth) % TEXT[5]->wdth;
		FL->ftexty = (int)(FL->currfloory * TEXT[5]->hght) % TEXT[5]->hght;
		color = *((unsigned int*)(TEXT[5]->data +
					(TEXT[5]->wdth * FL->ftexty * 4 + FL->ftextx * 4)));
		img_put_pixel(e, RC->x, i, color);
		ft_draw_sky(e, i);
	}
}
