/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 12:10:59 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/05 17:40:48 by jrosamon         ###   ########.fr       */
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

static void ft_create_texture(t_env *e)
{
	int i;
	int	lar;
	int	lon;

	i = 0;
	e->texture= (t_img**)malloc(sizeof(t_img) * 8);
	while (i < 8)
	{
		e->texture[i] = (t_img*)malloc(sizeof(t_img));
		i++;
	}
	e->texture[0] = mlx_xpm_file_to_image(e->mlx, "img/mossy.XPM", &lar, &lon);
}


static	void	ft_create_rc(t_env *e)
{
	if (!(e->rc = (t_raycast*)malloc(sizeof(t_raycast))))
		exit(EXIT_FAILURE);
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
	e->time = 0;
	e->oldtime = 0;	
	e->frametime = 0;
}

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_env	e;
	ft_init(&e);
	mlx_key_hook(e.win, &keyboard_event, &e);
	mlx_mouse_hook(e.win, &mouse_event, &e);
	mlx_expose_hook(e.win, &draw, &e);
	mlx_loop(e.mlx);
	return (0);
}
