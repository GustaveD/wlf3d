/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:17:56 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/11 16:58:05 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_sprite_init(t_env *e, int *sprite_order, int i)
{
	e->rc->s_x = e->sprite[sprite_order[i]]->x - PPOSX;
	e->rc->s_y = e->sprite[sprite_order[i]]->y - PPOSY;
	e->rc->invdet = 1.0 / (PPLANEX * PDIRY - PDIRX * PPLANEY);
	e->rc->transf_x = e->rc->invdet * (PDIRY * e->rc->s_x - PDIRX * e->rc->s_y);
	e->rc->transf_y = e->rc->invdet * (-(PPLANEY) * e->rc->s_x + PPLANEX * e->rc->s_y);
	e->rc->s_screenx = (int)((WIN_WIDTH / 2) * (1 + e->rc->transf_x / e->rc->transf_y));
	e->rc->s_height = abs((int)(WIN_HEIGHT / e->rc->transf_y));
	e->rc->dstarty = -(e->rc->s_height) / 2 + WIN_HEIGHT / 2;
	if (e->rc->dstarty < 0)
		e->rc->dstarty = 0;
	e->rc->dendy = e->rc->s_height / 2 + WIN_HEIGHT / 2;
	if (e->rc->dendy >= WIN_HEIGHT)
		e->rc->dendy = WIN_HEIGHT - 1;
	e->rc->s_width = abs((int)(WIN_HEIGHT / e->rc->transf_y));
	e->rc->dstartx = -(e->rc->s_width) / 2 + e->rc->s_screenx;
	if (e->rc->dstartx < 0)
		e->rc->dstartx = 0;
	e->rc->dendx = e->rc->s_width / 2 + e->rc->s_screenx;
	if (e->rc->dendx >= WIN_WIDTH)
		e->rc->dendx = WIN_WIDTH - 1;	
}

static int	*ft_order(t_env *e, int nb)
{
	int		i;
	int		*sprite_order;

	i = 0;
	sprite_order = (int*)malloc(sizeof(int) * nb);
	while (i < nb)
	{
		sprite_order[i] = i;
		e->sprite_distance[i] = ((PPOSX - e->sprite[i]->x) *
									(PPOSX - e->sprite[i]->x) +
									(PPOSY - e->sprite[i]->y) *
									(PPOSY - e->sprite[i]->y));
		i++;
	}
	comb_sort(sprite_order, e->sprite_distance, nb);
	return (sprite_order);
}

static void	ft_stripe_draw(t_env *e, int *sprite_order, int i, int stripe)
{
	int		tmp;
	int		d;
	int 	color;

	e->rc->y = e->rc->dstarty;
	while (e->rc->y < e->rc->dendy)
	{
		d = (e->rc->y) * 256 - WIN_HEIGHT * 128 + e->rc->s_height * 128;
		e->rc->texY = ((d * TEXT_HEIGHT) / e->rc->s_height) / 256;
		color = stripe * (e->bpp / 8) + e->rc->y * e->isizeline;
		tmp = e->rc->texX * (e->sprite[sprite_order[i]]->img->bpp / 8) + e->rc->texY *
								e->sprite[sprite_order[i]]->img->sizeline;
		e->idata[color] = e->sprite[sprite_order[i]]->img->data[tmp];
		e->idata[color + 1] = e->sprite[sprite_order[i]]->img->data[tmp + 1];
		e->idata[color + 2] = e->sprite[sprite_order[i]]->img->data[tmp + 2];
		e->idata[color + 3] = 1;
		e->rc->y++;
	}
}

void		sprite_cast(t_env *e, int nb)
{
	int		i;
	int		stripe;
	int		*sprite_order;

	sprite_order = ft_order(e, nb);
	i = 0;
	while (i < nb)
	{
		ft_sprite_init(e, sprite_order, i);
		stripe = e->rc->dstartx;
		while (stripe < e->rc->dendx)
		{
			e->rc->texX = (int)(256 * (stripe - (e->rc->s_screenx - e->rc->s_width / 2))
										* TEXT_WIDTH / e->rc->s_height / 256);
			if (e->rc->transf_y > 0 && stripe > 0 && stripe < WIN_WIDTH && 
					e->rc->transf_y < e->zbuffer[stripe])
				ft_stripe_draw(e, sprite_order, i, stripe);
			stripe++;	
		}
		i++;
	}
}
