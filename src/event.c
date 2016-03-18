/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:37:50 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/18 16:47:06 by jrosamon         ###   ########.fr       */
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
	action_player(e);
	draw(e);
	return (0);
}
