/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:37:50 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/18 11:51:00 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		create_key(t_env *e)
{
	if (!(e->key = (t_key*)malloc(sizeof(t_key))))
		return (0);
	ft_bzero(e->key, sizeof(t_key));
	return (1);
}

int		mouse_event(int button, int x, int y, t_env *e)
{
	(void)button;
	(void)x;
	(void)y;
	(void)e;
	return (0);
}

int		expose_hook(t_env *e)
{
	(void)e;
	return (0);
}

int		loop_hook(t_env *e)
{
	draw(e);
	return (0);
}

int		keyboard_event(int keycode, t_env *e)
{
	printf("keycode = %d\n", keycode);
	if (keycode == KEYCODE_EXIT)
		exit(EXIT_SUCCESS);
	if (keycode == 126)
	{
		if (!(e->map[(int)(PPOSX + PDIRX * PMOVS)][(int)(PPOSY)]))
			PPOSX += PDIRX * PMOVS;
		if (!(e->map[(int)(PPOSX)][(int)(PPOSY + PDIRY * PMOVS)]))
			PPOSY += PDIRY * PMOVS;
	}
	if (keycode == 123)
		move_player_left(e);
	if (keycode == 125)
	{
		if (!(e->map[(int)(PPOSX - PDIRX * PMOVS)][(int)(PPOSY)]))
			PPOSX -= PDIRX * PMOVS;
		if (!(e->map[(int)(PPOSX)][(int)(PPOSY - PDIRY * PMOVS)]))
			PPOSY -= PDIRY * PMOVS;
	}
	if (keycode == 124)
		move_player_right(e);
	if (keycode == 2)
		straffe_right(e);
	if (keycode == 0)
		straffe_left(e);
	draw(e);
	return (0);
}
