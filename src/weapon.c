/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:48:22 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/17 18:58:27 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			create_weapon(t_env *e)
{
	int la;
	int lo;

	if (!(e->gun = (t_img*)malloc(sizeof(t_img))))
		return (0);
	e->gun->i = mlx_xpm_file_to_image(e->mlx, "img/sprite/fucksprite.xpm", &la, &lo);
	e->gun->wdth = lo;
	e->gun->hght = la;
	e->gun->data = mlx_get_data_addr(e->gun->i, &e->gun->bpp, &e->gun->sizeline, &e->gun->endian);
	return (1);
}
