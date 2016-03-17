/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:17:56 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/17 19:07:27 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			ft_create_sprites(t_env *e)
{
	int i;
	int la;
	int lo;

	i = 0;
	if (!(e->sprite = (t_sprite**)malloc(sizeof(t_sprite) * NBSPRITE)))
		return (0);
	while (i < NBSPRITE)
	{
		if (!(e->sprite[i] = (t_sprite*)malloc(sizeof(t_sprite))))
			return (0);
		if (!(e->sprite[i]->img = (t_img*)malloc(sizeof(t_img))))
			return (0);
		e->sprite[i]->img->i =
			mlx_xpm_file_to_image(e->mlx, "img/sprite/policeman.xpm", &la, &lo);
		e->sprite[i]->img->data =
			mlx_get_data_addr(e->sprite[i]->img->i, &e->sprite[i]->img->bpp,
												&e->sprite[i]->img->sizeline,
												&e->sprite[i]->img->endian);
		i++;
	}
	ft_init_sprites(e);
	return (1);
}

static void		ft_sprite_init(t_env *e, int *sprite_order, int i)
{
	RC->s_x = e->sprite[sprite_order[i]]->x - PPOSX;
	RC->s_y = e->sprite[sprite_order[i]]->y - PPOSY;
	RC->invdet = 1.0 / (PPLANEX * PDIRY - PDIRX * PPLANEY);
	RC->transf_x = RC->invdet * (PDIRY * RC->s_x - PDIRX * RC->s_y);
	RC->transf_y = RC->invdet * (-(PPLANEY) * RC->s_x + PPLANEX * RC->s_y);
	RC->s_screenx = (int)((WIN_WIDTH / 2) * (1 + RC->transf_x / RC->transf_y));
	RC->s_height = abs((int)(WIN_HEIGHT / RC->transf_y));
	RC->dstarty = -(RC->s_height) / 2 + WIN_HEIGHT / 2;
	if (RC->dstarty < 0)
		RC->dstarty = 0;
	RC->dendy = RC->s_height / 2 + WIN_HEIGHT / 2;
	if (RC->dendy >= WIN_HEIGHT)
		RC->dendy = WIN_HEIGHT - 1;
	RC->s_width = abs((int)(WIN_HEIGHT / RC->transf_y));
	RC->dstartx = -(RC->s_width) / 2 + RC->s_screenx;
	if (RC->dstartx < 0)
		RC->dstartx = 0;
	RC->dendx = RC->s_width / 2 + RC->s_screenx;
	if (RC->dendx >= WIN_WIDTH)
		RC->dendx = WIN_WIDTH - 1;
}

static int		*ft_order(t_env *e, int nb)
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

static void		ft_stripe_draw(t_env *e, int *sprite_order, int i, int stripe)
{
	int		d;
	int		color;

	RC->y = RC->dstarty;
	while (RC->y < RC->dendy)
	{
		d = (RC->y) * 2 - WIN_HEIGHT * + RC->s_height;
		RC->texY = ((d * TEXT_HEIGHT / 2) / RC->s_height);
		color = *((unsigned int*)(e->sprite[sprite_order[i]]->img->i + (
						TEXT_WIDTH + RC->texY * 4 +
						RC->texX * 4)));
		img_put_pixel(e, stripe, RC->y, color);
		RC->y++;
	}
}

void			sprite_cast(t_env *e, int nb)
{
	int		i;
	int		stripe;
	int		*sprite_order;

	sprite_order = ft_order(e, nb);
	i = 0;
	while (i < nb)
	{
		ft_sprite_init(e, sprite_order, i);
		stripe = RC->dstartx;
		while (stripe < RC->dendx)
		{
			RC->texX = (int)(256 * (stripe - (RC->s_screenx - RC->s_width / 2))
										* TEXT_HEIGHT / RC->s_height / 256);
			if (RC->transf_y > 0 && stripe > 0 && stripe < WIN_WIDTH &&
					RC->transf_y < e->zbuffer[stripe])
				ft_stripe_draw(e, sprite_order, i, stripe);
			stripe++;
		}
		i++;
	}
}
