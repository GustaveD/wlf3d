/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 17:00:11 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/05 15:39:15 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		img_put_pixel(t_env *env, int x, int y, int color)
{
	unsigned int *udata;
	unsigned int sl_div;
	unsigned int bpp_div;

	udata = (unsigned int*)env->idata;
	sl_div = env->isizeline / 4;
	bpp_div = env->bpp / 8 / 4;
	udata[sl_div * y + bpp_div * x] = color;
	return ;
}

void	img_put_vline(t_env *env, t_vertex *v1, t_vertex *v2, int color)
{
	int i;
	
	//printf("color = %d\n", color);
	i = v1->y;	
	while (i < v2->y)
	{
		img_put_pixel(env, v1->x + ((v2->x - v1->x) *
			(i - v1->y)) / (v2->y - v1->y), i, color);
		i++;
	}
}

void		fill_img(t_env *env, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			img_put_pixel(env, i, j, color);
			j++;
		}
		i++;
	}
}
