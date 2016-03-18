/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:48:22 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/18 11:44:54 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			create_weapon(t_env *e)
{
	int la;
	int lo;

	if (!(e->gun = (t_sprite*)malloc(sizeof(t_sprite))))
		return (0);
	if (!(e->gun->img = (t_img*)malloc(sizeof(t_img))))
		return (0);
	e->gun->img->i = mlx_xpm_file_to_image(e->mlx, "img/sprite/fucksprite.xpm", &la, &lo);
	e->gun->img->wdth = lo;
	e->gun->img->hght = la;
	e->gun->img->data = mlx_get_data_addr(e->gun->img->i, &e->gun->img->bpp,
		   	&e->gun->img->sizeline, &e->gun->img->endian);
	e->gun->x = 500 / 2;
   	e->gun->y = 500 / 2;
	return (1);
}
