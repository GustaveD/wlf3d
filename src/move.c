/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 10:49:05 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/14 13:21:19 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		move_player_left(t_env *e)
{
	double old_dirx;
	double old_planex;

	old_dirx = PDIRX;
	old_planex = PPLANEX;
	PDIRX = PDIRX * cos(PROTS) - PDIRY * sin(PROTS);
	PDIRY = old_dirx * sin(PROTS) + PDIRY * cos(PROTS);
	PPLANEX = PPLANEX * cos(PROTS) - PPLANEY * sin(PROTS);
	PPLANEY = old_planex * sin(PROTS) + PPLANEY * cos(PROTS);
}

void		move_player_right(t_env *e)
{
	double old_dirx;
	double old_planex;

	old_dirx = PDIRX;
	old_planex = PPLANEX;
	PDIRX = PDIRX * cos(-PROTS) - PDIRY * sin(-PROTS);
	PDIRY = old_dirx * sin(-PROTS) + PDIRY * cos(-PROTS);
	PPLANEX = PPLANEX * cos(-PROTS) - PPLANEY * sin(-PROTS);
	PPLANEY = old_planex * sin(-PROTS) + PPLANEY * cos(-PROTS);
}

void		straffe_right(t_env *e)
{
	if (PDIRX >= -1 && PDIRX <= -0.8 && PDIRY > -0.8 && PDIRY <= 0.8)
	{
		if (!(e->map[(int)(PPOSX)][(int)(PPOSY + PMOVS)])
			&& !(e->map[(int)(PPOSX)][(int)(PPOSY + PMOVS)]))
			PPOSY = PPOSY + PMOVS;
	}
	if (PDIRX >= 1 && PDIRX <= 0.8 && PDIRY > 0.8 && PDIRY <= 0.8)
	{
		if (!(e->map[(int)(PPOSX)][(int)(PPOSY - PMOVS)]
			&& !(e->map[(int)(PPOSX)][(int)(PPOSY - PMOVS)])))
				PPOSY = PPOSY - PMOVS;
	}
	else if (PDIRX >= -0.8 && PDIRX <= 0.8 && PDIRY >= -1 && PDIRY < -0.5)
	{
		if (!(e->map[(int)(PPOSX - PMOVS)][(int)(PPOSY)]))
			PPOSX = PPOSX - PMOVS;
	}
	else if (PDIRX >= -0.8 && PDIRX <= 0.8 && PDIRY > 0.5 && PDIRY <= 1)
	{
		if (!(e->map[(int)(PPOSX + PMOVS)][(int)(PPOSY)]))
			PPOSX = PPOSX + PMOVS;
	}
}

void		straffe_left(t_env *e)
{
	if (PDIRX >= -1 && PDIRX <= -0.8 && PDIRY > -0.8 && PDIRY <= 0.8)
		if (e->map[(int)(PPOSX)][(int)(PPOSY - PMOVS)] == 0
			&& e->map[(int)(PPOSX)][(int)(PPOSY - PMOVS)] == 0)
							PPOSY = PPOSY - PMOVS;
	if (PDIRX >= 1 && PDIRX <= 0.8 && PDIRY > 0.8 && PDIRY <= 0.8)
	{
	if (e->map[(int)(PPOSX)][(int)(PPOSY + PMOVS)] == 0
						&& e->map[(int)(PPOSX)][(int)(PPOSY + PMOVS)] == 0)
					PPOSY = PPOSY + PMOVS;
	}
	else if (PDIRX >= -0.8 && PDIRX <= 0.8 && PDIRY >= -1 && PDIRY < -0.5)
	{
		if (e->map[(int)(PPOSX + PMOVS)][(int)(PPOSY)] == 0)
										PPOSX = PPOSX + PMOVS;
	}
	else if (PDIRX >= -0.8 && PDIRX <= 0.8 && PDIRY > 0.5 && PDIRY <= 1)
	{
		if (e->map[(int)(PPOSX - PMOVS)][(int)(PPOSY)] == 0)
			PPOSX = PPOSX - PMOVS;
	}
}
