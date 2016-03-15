/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 16:30:02 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/15 10:19:51 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_create_floor(t_env *e)
{
	if (!(FL = (t_floor*)malloc(sizeof(t_floor))))
		exit(EXIT_FAILURE);
	ft_bzero(FL, sizeof(t_floor));
}

void	ft_direction_floor(t_env *e)
{
	if (RC->side == 0 && RC->rayDirX > 0)
	{
		FL->fxwall = RC->mapX;
		FL->fywall = RC->mapY + RC->wallX;
	}
	else if (RC->side == 0 && RC->rayDirX < 0)
	{
		FL->fxwall = RC->mapX + 1.0;
		FL->fywall = RC->mapY + RC->wallX;
	}
	else if (RC->side == 1 && RC->rayDirY > 0)
	{
		FL->fxwall = RC->mapX + RC->wallX;
		FL->fywall = RC->mapY;
	}
	else
	{
		FL->fxwall = RC->mapX + RC->wallX;
		FL->fywall = RC->mapY + 1.0;
	}
	ft_draw_floor(e);
}

void	ft_draw_floor(t_env *e)
{
	int i;
	int color;

	i = RC->drawEnd + 1;
	FL->distwall = RC->perpWallDist;
	FL->distplayer = 0;
	if (RC->drawEnd < 0)
		RC->drawEnd = WIN_HEIGHT;
	while (i <= WIN_HEIGHT)
	{
		FL->currdist = WIN_HEIGHT / (2.0 * i - WIN_HEIGHT);
		FL->weight = (FL->currdist - FL->distplayer) /
							(FL->distwall - FL->distplayer);
		FL->currfloorx = FL->weight * FL->fxwall + (1.0 - FL->weight) * PPOSX;
		FL->currfloory = FL->weight * FL->fywall + (1.0 - FL->weight) * PPOSY;
		FL->ftextx = (int)(FL->currfloorx * TEXT[5]->wdth) % TEXT[5]->wdth;
		FL->ftexty = (int)(FL->currfloory * TEXT[5]->hght) % TEXT[5]->hght;
		color = *((unsigned int*)(TEXT[5]->data + (TEXT[5]->wdth * FL->ftexty * 4 + FL->ftextx * 4)));
		img_put_pixel(e, RC->x, i, color);
		img_put_pixel(e, RC->x, WIN_HEIGHT - i, color);
		i++;
	}
}
