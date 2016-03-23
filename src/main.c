/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 12:10:59 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/23 13:24:44 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		ft_create_player(t_env *e)
{
	if (!(e->p = (t_player*)malloc(sizeof(t_player))))
		return (0);
	if (!(e->p->pos = (t_vertex*)malloc(sizeof(t_vertex))))
		return (0);
	if (!(e->p->dir = (t_vertex*)malloc(sizeof(t_vertex))))
		return (0);
	if (!(e->p->plane = (t_vertex*)malloc(sizeof(t_vertex))))
		return (0);
	PPOSX = 22.0;
	PPOSY = 12.0;
	PDIRX = -1.0;
	PDIRY = 0.0;
	PPLANEX = 0.0;
	PPLANEY = 0.66;
	PROTS = 0;
	PMOVS = 0;
	e->time = 0;
	e->oldtime = 0;
	e->frametime = 0;
	e->textid = 0;
	e->idtext = 0;
	e->v_anim = 0;
	return (1);
}

static int		ft_create_rc(t_env *e)
{
	if (!(RC = (t_raycast*)malloc(sizeof(t_raycast))))
		return (0);
	ft_bzero(RC, sizeof(t_raycast));
	return (1);
}

static void		ft_init(t_env *e, int fd)
{
	e->mlx = mlx_init();
	if (!e->mlx)
		ft_putendl_fd("Error, failed to initiate mlx.", 2);
	e->win = mlx_new_window(e->mlx, WIN_WIDTH, WIN_HEIGHT, "Wolf3d");
	e->img = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->idata = mlx_get_data_addr(e->img, &e->bpp,
			&e->isizeline, &e->iendian);
	if (!(ft_create_map(e, fd)))
		ft_error(2, e, "ERR: create map failed\n");
	if (!(ft_create_player(e)))
		ft_error(2, e, "ERR: create player failed\n");
	if (!(ft_create_texture(e)))
		ft_error(2, e, "ERR: create texture failed\n");
	if (!(ft_create_rc(e)))
		ft_error(2, e, "ERR: create struct rc failed\n");
	if (!(ft_create_floor(e)))
		ft_error(2, e, "ERR: create floor failed\n");
	if (!(create_weapon(e)))
		ft_error(2, e, "ERR: create weapon failed\n");
	if (!(create_key(e)))
		ft_error(2, e, "ERR: create key failed\n");
}

int				main(int ac, char **av)
{
	t_env	e;
	int		fd;

	if (ac != 2)
		ft_error(2, &e, "ERR: Need a map\n");
	fd = open(av[ac - 1], O_RDONLY);
	ft_init(&e, fd);
	mlx_expose_hook(e.win, &expose_hook, &e);
	mlx_loop_hook(e.mlx, &loop_hook, &e);
	mlx_hook(e.win, 2, (1L << 0), key_pr, &e);
	mlx_hook(e.win, 3, (1L << 0), key_rel, &e);
	mlx_loop(e.mlx);
	return (0);
}
