/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 12:10:59 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/09 18:01:49 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void ft_create_player(t_env *e)
{
	if(!(e->p = (t_player*)malloc(sizeof(t_player))))
		return; 

	if (!(e->p->pos = (t_vertex*)malloc(sizeof(t_vertex))))
		return ;
	if (!(e->p->dir = (t_vertex*)malloc(sizeof(t_vertex))))
		return ;
	if (!(e->p->plane = (t_vertex*)malloc(sizeof(t_vertex))))
		return ;
	
	e->p->pos->x = 22.0;
	e->p->pos->y = 12.0;
	e->p->dir->x = -1.0;
	e->p->dir->y = 0.0;
	e->p->plane->x = 0.0;
	e->p->plane->y = 0.66;
	e->p->mv_speed = 0;
	e->p->mv_speed = 0;

}
static void		init_texture(t_env *e)
{
	int		i;
	
	i = 0;
	while (i < 6)
	{
		e->texture[i]->data = mlx_get_data_addr(e->texture[i]->data, &e->texture[i]->bpp,
												&e->texture[i]->sizeline, 
												&e->texture[i]->endian);
		i++;
	}
}

static void ft_create_texture(t_env *e)
{
	int i;
	int	lar;
	int	lon;

	i = 0;
	e->texture= (t_img**)malloc(sizeof(t_img) * 6);
	while (i < 6)
	{
		e->texture[i] = (t_img*)malloc(sizeof(t_img));
		i++;
	}
	e->texture[0]->data = mlx_xpm_file_to_image(e->mlx, "img/mossy.XPM", &lar, &lon);
	e->texture[1]->data = mlx_xpm_file_to_image(e->mlx, "img/eagle.XPM", &lar, &lon);
	e->texture[2]->data = mlx_xpm_file_to_image(e->mlx, "img/redbrick.XPM", &lar, &lon);
	e->texture[3]->data = mlx_xpm_file_to_image(e->mlx, "img/purplestone.XPM", &lar, &lon);
	e->texture[4]->data = mlx_xpm_file_to_image(e->mlx, "img/purplestone.XPM", &lar, &lon);
	e->texture[5]->data = mlx_xpm_file_to_image(e->mlx, "img/wood.XPM", &lar, &lon);
	init_texture(e);
}


static	void	ft_create_rc(t_env *e)
{
	if (!(e->rc = (t_raycast*)malloc(sizeof(t_raycast))))
		exit(EXIT_FAILURE);
	e->rc->x = 0;
	e->rc->y = 0;
	e->rc->cameraX = 0;
	e->rc->rayPosX = 0;	
	e->rc->rayPosY = 0;	
	e->rc->rayDirY = 0;	
	e->rc->rayDirX = 0;
	e->rc->mapX = 0;
	e->rc->mapY = 0;
	e->rc->sideDistX = 0;
	e->rc->sideDistY = 0;
	e->rc->deltaDistX = 0;
	e->rc->deltaDistY = 0;
	e->rc->perpWallDist = 0;
	e->rc->stepX = 0;
	e->rc->stepY = 0;
	e->rc->hit = 0;
	e->rc->side = 0;
	e->rc->lineHeight = 0;
	e->rc->drawStart = 0;
	e->rc->drawEnd = 0;
	e->rc->wallX = 0;
	e->rc->texX = 0;
	e->rc->texY = 0;
	e->rc->i = 0;
}

static	void		ft_create_floor(t_env *e)
{
	if (!(e->fl = (t_floor*)malloc(sizeof(t_floor))))
		exit(EXIT_FAILURE);
	e->fl->fxwall = 0;
	e->fl->fywall = 0;
	e->fl->distwall = 0;
	e->fl->distplayer = 0;
	e->fl->currdist = 0;
	e->fl->weight = 0;
	e->fl->currfloorx = 0;	
	e->fl->currfloory = 0;	
	e->fl->ftextx = 0;
	e->fl->ftexty = 0;
}


static void	ft_init(t_env *e)
{
	e->mlx = mlx_init();
	if (!e->mlx)
	{
		ft_putendl_fd("Error, failed to initiate mlx.", 2);
		exit(EXIT_FAILURE);
	}
	e->win = mlx_new_window(e->mlx, WIN_WIDTH, WIN_HEIGHT, "Wolf3d");
	e->img = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->idata = mlx_get_data_addr(e->img, &e->bpp,
			&e->isizeline, &e->iendian);
	ft_create_player(e);
	ft_create_texture(e);
	ft_create_rc(e);
	ft_create_floor(e);
	e->time = 0;
	e->oldtime = 0;	
	e->frametime = 0;
	e->textid = 0;
}

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_env	e;
	ft_init(&e);
	mlx_key_hook(e.win, &keyboard_event, &e);
	mlx_mouse_hook(e.win, &mouse_event, &e);
	mlx_expose_hook(e.win, &expose_hook, &e);
	mlx_loop_hook(e.mlx, &loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
