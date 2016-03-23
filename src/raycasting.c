/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 16:40:36 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/23 19:01:35 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void			ft_draw_buff(t_env *e)
{
	RC->line_hght = (int)(WIN_HEIGHT / RC->perp_wall_d);
	RC->draw_start = -RC->line_hght / 2 + WIN_HEIGHT / 2;
	if (RC->draw_start < 0)
		RC->draw_start = 0;
	RC->draw_end = RC->line_hght / 2 + WIN_HEIGHT / 2;
	if (RC->draw_end >= WIN_HEIGHT)
		RC->draw_end = WIN_HEIGHT - 1;
	e->textid = e->map[RC->mapy][RC->mapx];
	draw_text_2(e);
}

static void			ft_dda(t_env *e)
{
	while (RC->hit == 0)
	{
		if (RC->side_dx < RC->side_dy)
		{
			RC->side_dx += RC->delta_dx;
			RC->mapx += RC->step_x;
			RC->side = 0;
		}
		else
		{
			RC->side_dy += RC->delta_dy;
			RC->mapy += RC->step_y;
			RC->side = 1;
		}
		if (e->map[RC->mapx][RC->mapy] > 0)
			RC->hit = 1;
	}
	if (RC->side == 0)
		RC->perp_wall_d = (RC->mapx - RC->ray_posx + (1 - RC->step_x) / 2)
							/ RC->ray_dirx;
	else
		RC->perp_wall_d = (RC->mapy - RC->ray_posy + (1 - RC->step_y) / 2)
							/ RC->ray_diry;
}

static void			ft_init_ray(t_env *e)
{
	RC->camera_x = 2 * RC->x / (double)WIN_WIDTH - 1;
	RC->ray_posx = PPOSX;
	RC->ray_posy = PPOSY;
	RC->ray_dirx = PDIRX + PPLANEX * RC->camera_x;
	RC->ray_diry = PDIRY + PPLANEY * RC->camera_x;
	RC->mapx = (int)RC->ray_posx;
	RC->mapy = (int)RC->ray_posy;
	RC->delta_dx = sqrt(1 + (RC->ray_diry * RC->ray_diry) /
								(RC->ray_dirx * RC->ray_dirx));
	RC->delta_dy = sqrt(1 + (RC->ray_dirx * RC->ray_dirx) /
								(RC->ray_diry * RC->ray_diry));
	RC->hit = 0;
	if (RC->ray_dirx < 0)
		RC->step_x = -1;
	else
		RC->step_x = 1;
	if (RC->ray_diry < 0)
		RC->step_y = -1;
	else
		RC->step_y = 1;
}

void				ft_raycasting(t_env *e)
{
	RC->x = 0;
	while (RC->x < WIN_WIDTH)
	{
		ft_init_ray(e);
		if (RC->ray_dirx < 0)
			RC->side_dx = (RC->ray_posx - RC->mapx) * RC->delta_dx;
		else
			RC->side_dx = (RC->mapx + 1.0 - RC->ray_posx) * RC->delta_dx;
		if (RC->ray_diry < 0)
			RC->side_dy = (RC->ray_posy - RC->mapy) * RC->delta_dy;
		else
			RC->side_dy = (RC->mapy + 1.0 - RC->ray_posy) * RC->delta_dy;
		ft_dda(e);
		ft_draw_buff(e);
		e->zbuffer[RC->x] = RC->perp_wall_d;
		ft_direction_floor(e);
		RC->x++;
	}
}
