/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 12:10:59 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/14 14:46:15 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		ft_create_player(t_env *e)
{
	if (!(e->p = (t_player*)malloc(sizeof(t_player))))
		return ;
	if (!(e->p->pos = (t_vertex*)malloc(sizeof(t_vertex))))
		return ;
	if (!(e->p->dir = (t_vertex*)malloc(sizeof(t_vertex))))
		return ;
	if (!(e->p->plane = (t_vertex*)malloc(sizeof(t_vertex))))
		return ;
	PPOSX = 22.0;
	PPOSY = 12.0;
	PDIRX = -1.0;
	PDIRY = 0.0;
	PPLANEX = 0.0;
	PPLANEY = 0.66;
	PROTS = 0;
	PMOVS = 0;
}

static void		ft_create_rc(t_env *e)
{
	if (!(RC = (t_raycast*)malloc(sizeof(t_raycast))))
		exit(EXIT_FAILURE);
	ft_bzero(RC, sizeof(t_raycast));
}

void			ft_init_sprites(t_env *e)
{
	int		i;
	double	x;
	double	y;

	x = 5.0;
	y = 5.0;
	i = 0;
	while (i < NBSPRITE)
	{
		x += 5.0;
		y += 5.0;
		e->sprite[i]->x = x;
		e->sprite[i]->y = y;
		i++;
	}
}

static void		ft_init(t_env *e, int fd)
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
	e->sprite_distance = (double*)malloc(sizeof(double) * NBSPRITE);
	ft_create_map(e, fd);
	ft_create_player(e);
	ft_create_texture(e);
	ft_create_rc(e);
	ft_create_floor(e);
	ft_create_sprites(e);
	e->time = 0;
	e->oldtime = 0;
	e->frametime = 0;
	e->textid = 0;
}

int				main(int ac, char **av)
{
	t_env	e;
	int		fd;

	if (ac == 1)
		exit(EXIT_FAILURE);
	fd = open(av[ac - 1], O_RDONLY);
	ft_init(&e, fd);
	mlx_key_hook(e.win, &keyboard_event, &e);
	mlx_mouse_hook(e.win, &mouse_event, &e);
	mlx_expose_hook(e.win, &expose_hook, &e);
	mlx_loop_hook(e.mlx, &loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
