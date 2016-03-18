/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:50:48 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/18 16:44:57 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			ft_error(int err, t_env *e, char *s)
{
	if (e)
	{
		e->img != NULL ?
			mlx_destroy_image(e->mlx, e->img) : 0;
		e->win != NULL ?
			mlx_destroy_window(e->mlx, e->win) : 0;
	}
	if (s)
		ft_putstr_fd(s, err);
	exit(0);
}
