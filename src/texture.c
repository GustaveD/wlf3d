/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 11:33:46 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/09 18:01:51 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		set_text(t_env *e, double y)
{

	e->rc->i = (int)((e->bpp >> 3) * ((ceil(e->rc->y) * (e->isizeline >> 2))
				+ (int)(e->rc->x)));
	e->idata[e->rc->i + 0] = e->texture[e->textid]->data[(e->texture[e->textid]->bpp >> 3) *
							((int)(y) * e->texture[e->textid]->sizeline >> 2) +
							e->rc->texX + 0];
	e->idata[e->rc->i + 1] = e->texture[e->textid]->data[(e->texture[e->textid]->bpp >> 3) *
							((int)(y) * e->texture[e->textid]->sizeline >> 2) +
							e->rc->texX + 1];
	e->idata[e->rc->i + 2] = e->texture[e->textid]->data[(e->texture[e->textid]->bpp >> 3) *
							((int)(y) * e->texture[e->textid]->sizeline >> 2) +
							e->rc->texX + 2];
}

void		get_text(t_env *e)
{
	if (e->rc->side == 0)
		e->rc->wallX = e->rc->rayPosY + e->rc->perpWallDist * e->rc->rayDirY;
	else
		e->rc->wallX = e->rc->rayPosX + e->rc->perpWallDist * e->rc->rayDirX;

	e->rc->wallX -= floor(e->rc->wallX);
	e->rc->texX = (int)(e->rc->wallX * (double)(TEXT_WIDTH));
	if (e->rc->side == 0 && e->rc->rayDirX > 0)
		e->rc->texX = TEXT_WIDTH - e->rc->texX - 1;
	else if (e->rc->side == 1 && e->rc->rayDirY < 0)
		e->rc->texX = TEXT_WIDTH - e->rc->texX -1;
}

void		draw_text(t_env *e)
{
	
	int		d;
	int		i;
	int		tmp;

	get_text(e);
	e->rc->y = (double)(e->rc->drawStart);
	while (e->rc->y <= e->rc->drawEnd)
	{
		d = e->rc->y * 256 - WIN_HEIGHT * 128 + e->rc->lineHeight * 128;
		e->rc->texY = ((d * TEXT_HEIGHT) / e->rc->lineHeight) / 256;
		i = e->rc->x * (e->bpp / 8) + e->rc->y * e->isizeline;
		tmp = e->rc->texX * (e->texture[e->textid]->bpp / 8) + e->rc->texY *
								e->texture[e->textid]->sizeline;
		e->idata[i] = e->texture[e->textid]->data[tmp];
		e->idata[i + 1] = e->texture[e->textid]->data[tmp + 1];
		e->idata[i + 2] = e->texture[e->textid]->data[tmp + 2];
		e->idata[i + 3] = 1;
		e->rc->y++;
	}
}

