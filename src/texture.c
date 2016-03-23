/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 11:33:46 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/23 12:14:48 by jrosamon         ###   ########.fr       */
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
		mlx_xpm_file_to_image(e->mlx, "img/text/stone1.xpm", &lar, &lon);
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
	if (RC->side == 1 && RC->ray_diry > 0)
		e->idtext = 0;
	if (RC->side == 1 && RC->ray_diry <= 0)
		e->idtext = 1;
	if (RC->side == 0 && RC->ray_dirx > 0)
		e->idtext = 2;
	if (RC->side == 0 && RC->ray_dirx <= 0)
		e->idtext = 3;
	if (RC->side == 0)
		RC->wall_x = RC->ray_posy + RC->perp_wall_d * RC->ray_diry;
	else
		RC->wall_x = RC->ray_posx + RC->perp_wall_d * RC->ray_dirx;
	RC->wall_x -= floor(RC->wall_x);
	RC->tex_x = (int)(RC->wall_x * (double)(TEXT[e->idtext]->wdth));
	if (RC->side == 0 && RC->ray_dirx > 0)
		RC->tex_x = TEXT[e->idtext]->wdth - RC->tex_x - 1;
	else if (RC->side == 1 && RC->ray_diry < 0)
		RC->tex_x = TEXT[e->idtext]->wdth - RC->tex_x - 1;
}

void			draw_text_2(t_env *e)
{
	int		d;
	int		color;

	get_text(e);
	RC->y = (double)(RC->draw_start);
	while (RC->y < RC->draw_end)
	{
		d = RC->y * 256 - WIN_HEIGHT * 128 + RC->line_hght * 128;
		RC->tex_y = ((d * TEXT[e->idtext]->hght) / RC->line_hght) / 256;
		color = *((unsigned int*)(TEXT[e->idtext]->data +
					(TEXT[e->idtext]->wdth * RC->tex_y * 4 + RC->tex_x * 4)));
		img_put_pixel(e, RC->x, RC->y, color);
		RC->y++;
	}
}
