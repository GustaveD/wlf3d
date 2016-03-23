/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:48:22 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/23 17:47:44 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		init_weapon(t_env *e)
{
	int la;
	int lo;

	e->gun[0]->img->i = mlx_xpm_file_to_image(e->mlx, "img/sprite/ft.xpm",
			&la, &lo);
	e->gun[0]->img->wdth = lo;
	e->gun[0]->img->hght = la;
	e->gun[0]->img->data = mlx_get_data_addr(e->gun[0]->img->i,
			&e->gun[0]->img->bpp, &e->gun[0]->img->sizeline,
			&e->gun[0]->img->endian);
	e->gun[0]->x = WIN_WIDTH / 2 - 100;
	e->gun[0]->y = 350;
	e->gun[1]->img->i = mlx_xpm_file_to_image(e->mlx, "img/sprite/ft2.xpm",
			&la, &lo);
	e->gun[1]->img->wdth = lo;
	e->gun[1]->img->hght = la;
	e->gun[1]->img->data = mlx_get_data_addr(e->gun[1]->img->i,
			&e->gun[1]->img->bpp,
			&e->gun[1]->img->sizeline, &e->gun[1]->img->endian);
	e->gun[1]->x = WIN_WIDTH / 2 - 100;
	e->gun[1]->y = 350;
}

int				create_weapon(t_env *e)
{
	int i;

	i = 0;
	if (!(e->gun = (t_sprite**)malloc(sizeof(t_sprite) * 2)))
		return (0);
	while (i < 2)
	{
		if (!(e->gun[i] = (t_sprite*)malloc(sizeof(t_sprite))))
			return (0);
		if (!(e->gun[i]->img = (t_img*)malloc(sizeof(t_img))))
			return (0);
		i++;
	}
	init_weapon(e);
	return (1);
}

static void		anim_weapon(t_env *e)
{
	if (e->key->run)
		e->v_anim = 8;
	else
		e->v_anim = 5;
	if (e->key->move && !e->key->anim)
	{
		if (e->gun[0]->y > 300 && e->gun[1]->y > 300)
		{
			e->gun[0]->y -= e->v_anim;
			e->gun[1]->y -= e->v_anim;
		}
		else
			e->key->anim = 1;
	}
	else
	{
		if (e->gun[0]->y < 350 && e->gun[1]->y < 350)
		{
			e->gun[0]->y += e->v_anim;
			e->gun[1]->y += e->v_anim;
		}
		else
			e->key->anim = 0;
	}
}

void			draw_weapon(t_env *e)
{
	anim_weapon(e);
	if (!(e->key->shoot))
		mlx_put_image_to_window(e->mlx, e->win, e->gun[0]->img->i,
			e->gun[0]->x, e->gun[0]->y);
	if (e->key->shoot)
		mlx_put_image_to_window(e->mlx, e->win, e->gun[1]->img->i,
			e->gun[1]->x, e->gun[1]->y);
}
