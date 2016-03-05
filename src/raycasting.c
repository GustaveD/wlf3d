/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 16:40:36 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/05 17:40:46 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		ft_draw_buff(t_env *e)
{
	e->rc->lineHeight = (int)(WIN_HEIGHT / e->rc->perpWallDist);
	e->rc->drawStart = -e->rc->lineHeight / 2 + WIN_HEIGHT / 2;
	if (e->rc->drawStart < 0)
		e->rc->drawStart = 0;
	e->rc->drawEnd = e->rc->lineHeight / 2 + WIN_HEIGHT /2;
	if (e->rc->drawEnd >= WIN_HEIGHT)
		e->rc->drawEnd = WIN_HEIGHT - 1;

	t_color color;
	choose_color(&color, 0, 144, 133);
	switch(worldMap[e->rc->mapX][e->rc->mapX])
	{
		case 1: choose_color(&color, 0, 144, 233);	
		case 2: choose_color(&color, 0, 144, 233);	
		case 3: choose_color(&color, 100, 144, 233);	
		case 4: choose_color(&color, 0, 144, 133);	
		default: choose_color(&color, 0, 244, 33);	
	}
	int	colorr = color_in_int(&color);
	if (e->rc->side == 1)
	{
		colorr = colorr / 2;
	}
	t_vertex *start = NULL;
	t_vertex *end = NULL;
	start = (t_vertex*)malloc(sizeof(t_vertex));
	end = (t_vertex*)malloc(sizeof(t_vertex));
	start->x = e->rc->x;
	start->y = e->rc->drawStart;
	end->x =e->rc-> x;
	end->y = e->rc->drawEnd;
	img_put_vline(e, start, end, colorr);
}

static void		ft_dda(t_env *e)
{
	while (e->rc->hit == 0)
	{
		if (e->rc->sideDistX < e->rc->sideDistY)
		{
			e->rc->sideDistX += e->rc->deltaDistX;
			e->rc->mapX += e->rc->stepX;
			e->rc->side = 0;
		}
		else
		{
			e->rc->sideDistY += e->rc->deltaDistY;
			e->rc->mapY += e->rc->stepY;
			e->rc->side = 1;
		}
		if (worldMap[e->rc->mapX][e->rc->mapY] > 0)
			e->rc->hit = 1;
	}
	if	(e->rc->side == 0)
		e->rc->perpWallDist = (e->rc->mapX - e->rc->rayPosX + (1 - e->rc->stepX) / 2) / e->rc->rayDirX;
	else
		e->rc->perpWallDist = (e->rc->mapY - e->rc->rayPosY + (1 - e->rc->stepY) / 2) / e->rc->rayDirY;
}

static void		ft_init_ray(t_env *e)
{
	e->rc->cameraX = 2 * e->rc->x / (double)WIN_WIDTH - 1;
	e->rc->rayPosX = PPOSX;
	e->rc->rayPosY = PPOSY;
	e->rc->rayDirX = PDIRX + PPLANEX * e->rc->cameraX;
	e->rc->rayDirY = PDIRY + PPLANEY * e->rc->cameraX;
	e->rc->mapX = (int)e->rc->rayPosX;
	e->rc->mapY = (int)e->rc->rayPosY;
	e->rc->deltaDistX = sqrt(1 + (e->rc->rayDirY * e->rc->rayDirY) /
								(e->rc->rayDirX * e->rc->rayDirX));
	e->rc->deltaDistY = sqrt(1 + (e->rc->rayDirX * e->rc->rayDirX) /
								(e->rc->rayDirY * e->rc->rayDirY));
	e->rc->hit = 0;
	if (e->rc->rayDirX < 0)
		e->rc->stepX = -1;
	else
		e->rc->stepX = 1;
	if (e->rc->rayDirY < 0)
		e->rc->stepY = -1;
	else
		e->rc->stepY = 1;
			
}

void	ft_raycasting(t_env *e)
{
	for (e->rc->x = 0; e->rc->x < WIN_WIDTH; e->rc->x++)
	{
		ft_init_ray(e);
		if (e->rc->rayDirX < 0)
			e->rc->sideDistX = (e->rc->rayPosX - e->rc->mapX) * e->rc->deltaDistX;
		else
			e->rc->sideDistX = (e->rc->mapX + 1.0 - e->rc->rayPosX) * e->rc->deltaDistX;
		if (e->rc->rayDirY < 0)
			e->rc->sideDistY = (e->rc->rayPosY - e->rc->mapY) * e->rc->deltaDistY;
		else
			e->rc->sideDistY = (e->rc->mapY + 1.0 - e->rc->rayPosY) * e->rc->deltaDistY;
		ft_dda(e);
		ft_draw_buff(e);
	}
}
