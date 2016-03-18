/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 13:42:48 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/18 16:42:07 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		key_pr(int key, t_env *e)
{
	key == KEYCODE_EXIT ? ft_error(1, e, "Quit\n") : 0;
	key == 126 ? e->key->up		= 1 : 0;
	key == 123 ? e->key->left	= 1 : 0;
	key == 124 ? e->key->right	= 1 : 0;
	key == 125 ? e->key->down	= 1 : 0;
	key == 1 ? e->key->shoot = 1 : 0;
	key == 2 ? e->key->s_right = 1 : 0;
	key == 0 ? e->key->s_left = 1 : 0;
	key == 15 ? e->key->run = 1 : 0;
	e->key->move = 1;
	return (1);
}

int		key_rel(int key, t_env *e)
{
	printf("key = %d\n", key);
	key == 126 ? e->key->up		= 0 : 0;
	key == 123 ? e->key->left	= 0 : 0;
	key == 124 ? e->key->right	= 0 : 0;
	key == 125 ? e->key->down	= 0 : 0;
	key == 1 ? e->key->shoot = 0 : 0;
	key == 2 ? e->key->s_right = 0 : 0;
	key == 0 ? e->key->s_left = 0 : 0;
	key == 15 ? e->key->run = 0 : 0;
	e->key->move = 0;
	return (1);
}

int		move_player(t_env *e)
{
	if (e->key->up)
	{
		if (!(e->map[(int)(PPOSX + PDIRX * PMOVS)][(int)(PPOSY)]))
			PPOSX += PDIRX * PMOVS;
		if (!(e->map[(int)(PPOSX)][(int)(PPOSY + PDIRY * PMOVS)]))
			PPOSY += PDIRY * PMOVS;
	}

	if (e->key->down)
	{	
		if (!(e->map[(int)(PPOSX - PDIRX * PMOVS)][(int)(PPOSY)]))
			PPOSX -= PDIRX * PMOVS;
		if (!(e->map[(int)(PPOSX)][(int)(PPOSY - PDIRY * PMOVS)]))
			PPOSY -= PDIRY * PMOVS;
	}
	if (e->key->right)
		move_player_right(e);
	if (e->key->left)
		move_player_left(e);
	if (e->key->s_right)
		straffe_right(e);
	if (e->key->s_left)
		straffe_left(e);
	return (1);
}

int		action_player(t_env *e)
{
	if (e->key->up || e->key->down || e->key->left || e->key->right ||
			e->key->s_right || e->key->s_left)
		move_player(e);
	return (1);
}
