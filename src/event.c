/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:37:50 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/04 15:40:54 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		mouse_event(int button, int x, int y, t_env *e)
{
	(void)button;
	(void)x;
	(void)y;
	(void)e;
	return (0);
}

int		keyboard_event(int keycode, t_env *e)
{
	if (keycode == KEYCODE_EXIT)
		exit(EXIT_SUCCESS);
	if (keycode == 126)
	{
		if (!(worldMap[(int)(PPOSX + PDIRX * PMOVS)][(int)(PPOSY)]))
			PPOSX += PDIRX * PMOVS;
		if (!(worldMap[(int)(PPOSX)][(int)(PPOSY + PDIRY * PMOVS)]))
			PPOSY += PDIRY * PMOVS;

	}
	if (keycode == 123)
	{
		double oldDirX = PDIRX;
		PDIRX = PDIRX * cos(PROTS) - PDIRY * sin(PROTS);
		PDIRY = oldDirX * sin(PROTS) + PDIRY * cos(PROTS);
		double oldPlaneX = PPLANEX;
		PPLANEX = PPLANEX = cos(PROTS) - PPLANEY * sin(PROTS);
		PPLANEY = oldPlaneX * sin(PROTS) + PPLANEY * cos(PROTS);

	}
	if (keycode == 125)
	{
		if (!(worldMap[(int)(PPOSX - PDIRX * PMOVS)][(int)(PPOSY)]))
			PPOSX -= PDIRX * PMOVS;
		if (!(worldMap[(int)(PPOSX)][(int)(PPOSY - PDIRY * PMOVS)]))
			PPOSY -= PDIRY * PMOVS;
	}
	if (keycode == 124)
	{
		double oldDirX = PDIRX;
		PDIRX = PDIRX * cos(-PROTS) - PDIRY * sin(-PROTS);
		PDIRY = oldDirX * sin(-PROTS) + PDIRY * cos(-PROTS);
		double oldPlaneX = PPLANEX;
		PPLANEX = PPLANEX = cos(-PROTS) - PPLANEY * sin(-PROTS);
		PPLANEY = oldPlaneX * sin(-PROTS) + PPLANEY * cos(-PROTS);
	}
	draw(e);
	return (0);
}
