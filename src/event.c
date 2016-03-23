/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:37:50 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/23 18:18:28 by jrosamon         ###   ########.fr       */
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
