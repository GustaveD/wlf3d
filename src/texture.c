/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 11:33:46 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/20 20:20:55 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			init_texture(t_env *e)
{
	int i;

	i = 0;
	while (i < 6)
	{
		TEXT[i]->data = mlx_get_data_addr(TEXT[i]->data, &TEXT[i]->bpp,
												&TEXT[i]->sizeline,
												&TEXT[i]->endian);
		i++;
	}
}

static void		ft_load_text(t_env *e)
{
	int lar;
	int lon;

	TEXT[0]->data =
		mlx_xpm_file_to_image(e->mlx, "img/text/stone2.xpm", &lar, &lon);
	TEXT[0]->wdth = lon;
	TEXT[0]->hght = lar;
	TEXT[1]->data =
		mlx_xpm_file_to_image(e->mlx, "img/text/redbrick.XPM", &lar, &lon);
	TEXT[1]->wdth = lon;
	TEXT[1]->hght = lar;
	TEXT[2]->data =
		mlx_xpm_file_to_image(e->mlx, "img/text/stone3.xpm", &lar, &lon);
	TEXT[2]->wdth = lon;
	TEXT[2]->hght = lar;
	TEXT[3]->data =
		mlx_xpm_file_to_image(e->mlx, "img/text/stone4.xpm", &lar, &lon);
	TEXT[4]->data =
		mlx_xpm_file_to_image(e->mlx, "img/text/stone5.xpm", &lar, &lon);
	TEXT[4]->wdth = lon;
	TEXT[4]->hght = lar;
	TEXT[5]->data =
		mlx_xpm_file_to_image(e->mlx, "img/text/floor1.xpm", &lar, &lon);
	TEXT[5]->wdth = lon;
	TEXT[5]->hght = lar;
}

int				ft_create_texture(t_env *e)
{
	int i;

	i = 0;
	if (!(TEXT = (t_img**)malloc(sizeof(t_img) * 6)))
		return (0);
	while (i < 6)
	{
		if (!(TEXT[i] = (t_img*)malloc(sizeof(t_img))))
			return (0);
		i++;
	}
	ft_load_text(e);
	init_texture(e);
	return (1);
}

void			get_text(t_env *e)
{
	if (RC->side == 0)
		RC->wallX = RC->rayPosY + RC->perpWallDist * RC->rayDirY;
	else
		RC->wallX = RC->rayPosX + RC->perpWallDist * RC->rayDirX;
	RC->wallX -= floor(RC->wallX);
	RC->texX = (int)(RC->wallX * (double)(TEXT[e->textid]->wdth));
	if (RC->side == 0 && RC->rayDirX > 0)
		RC->texX = TEXT[e->textid]->wdth - RC->texX - 1;
	else if (RC->side == 1 && RC->rayDirY < 0)
		RC->texX = TEXT[e->textid]->wdth - RC->texX - 1;
}

void			draw_text_2(t_env *e)
{
	int		d;
	int		color;

	if (RC->side == 1 && RC->rayDirY > 0)
		e->textid = 0;
	if (RC->side == 1 && RC->rayDirY <= 0)
		e->textid = 1;
	if (RC->side == 0 && RC->rayDirX > 0)
		e->textid = 2;
	if (RC->side == 0 && RC->rayDirX <= 0)
		e->textid = 3;
	get_text(e);
	RC->y = (double)(RC->drawStart);
	while (RC->y < RC->drawEnd)
	{
		d = RC->y * 258 - WIN_HEIGHT * 128 + RC->lineHeight * 128;
		RC->texY = ((d * TEXT[e->textid]->hght) / RC->lineHeight) / 256;
		color = *((unsigned int*)(TEXT[e->textid]->data +
					(TEXT[e->textid]->wdth * RC->texY * 4 + RC->texX * 4)));
		img_put_pixel(e, RC->x, RC->y, color);
		RC->y++;
	}
}
