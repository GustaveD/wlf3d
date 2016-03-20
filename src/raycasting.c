/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 16:40:36 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/20 19:20:21 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void			ft_draw_buff(t_env *e)
{
	RC->lineHeight = (int)(WIN_HEIGHT / RC->perpWallDist);
	RC->drawStart = -RC->lineHeight / 2 + WIN_HEIGHT / 2;
	if (RC->drawStart < 0)
		RC->drawStart = 0;
	RC->drawEnd = RC->lineHeight / 2 + WIN_HEIGHT / 2;
	if (RC->drawEnd >= WIN_HEIGHT)
		RC->drawEnd = WIN_HEIGHT - 1;
	e->textid = e->map[RC->mapY][RC->mapX];
	draw_text_2(e);
}

static void			ft_dda(t_env *e)
{
	while (RC->hit == 0)
	{
		if (RC->sideDistX < RC->sideDistY)
		{
			RC->sideDistX += RC->deltaDistX;
			RC->mapX += RC->stepX;
			RC->side = 0;
		}
		else
		{
			RC->sideDistY += RC->deltaDistY;
			RC->mapY += RC->stepY;
			RC->side = 1;
		}
		if (e->map[RC->mapX][RC->mapY] > 0)
			RC->hit = 1;
	}
	if (RC->side == 0)
		RC->perpWallDist = (RC->mapX - RC->rayPosX + (1 - RC->stepX) / 2)
							/ RC->rayDirX;
	else
		RC->perpWallDist = (RC->mapY - RC->rayPosY + (1 - RC->stepY) / 2)
							/ RC->rayDirY;
}

static void			ft_init_ray(t_env *e)
{
	RC->cameraX = 2 * RC->x / (double)WIN_WIDTH - 1;
	RC->rayPosX = PPOSX;
	RC->rayPosY = PPOSY;
	RC->rayDirX = PDIRX + PPLANEX * RC->cameraX;
	RC->rayDirY = PDIRY + PPLANEY * RC->cameraX;
	RC->mapX = (int)RC->rayPosX;
	RC->mapY = (int)RC->rayPosY;
	RC->deltaDistX = sqrt(1 + (RC->rayDirY * RC->rayDirY) /
								(RC->rayDirX * RC->rayDirX));
	RC->deltaDistY = sqrt(1 + (RC->rayDirX * RC->rayDirX) /
								(RC->rayDirY * RC->rayDirY));
	RC->hit = 0;
	if (RC->rayDirX < 0)
		RC->stepX = -1;
	else
		RC->stepX = 1;
	if (RC->rayDirY < 0)
		RC->stepY = -1;
	else
		RC->stepY = 1;
}

void				ft_raycasting(t_env *e)
{
	RC->x = 0;
	while (RC->x < WIN_WIDTH)
	{
		ft_init_ray(e);
		if (RC->rayDirX < 0)
			RC->sideDistX = (RC->rayPosX - RC->mapX) * RC->deltaDistX;
		else
			RC->sideDistX = (RC->mapX + 1.0 - RC->rayPosX) * RC->deltaDistX;
		if (RC->rayDirY < 0)
			RC->sideDistY = (RC->rayPosY - RC->mapY) * RC->deltaDistY;
		else
			RC->sideDistY = (RC->mapY + 1.0 - RC->rayPosY) * RC->deltaDistY;
		ft_dda(e);
		ft_draw_buff(e);
		e->zbuffer[RC->x] = RC->perpWallDist;
		ft_direction_floor(e);
		//sprite_cast(e, NBSPRITE);
		RC->x++;
	}
}
