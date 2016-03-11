/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:11:02 by jrosamon          #+#    #+#             */
/*   Updated: 2016/03/11 14:17:53 by jrosamon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		ft_swap(int *order, double *dist, int amount, int gap)
{
	int		i;
	int		j;
	int		tmp;
	double	temp;
	int		swap;

	i = 0;
	swap = 0;
	while (i < amount - gap)
	{
		j = i + gap;
		if (dist[i] < dist[j])
		{
			temp = dist[i];
			dist[i] = dist[j];
			dist[j] = temp;
			tmp = order[i];
			order[i] = order[j];
			order[j] = tmp;
			swap = 1;
		}
		i++;
	}
	return (swap);
}

void			comb_sort(int *order, double *dist, int amount)
{
	int			gap;
	int			swap;

	gap = amount;
	swap = 0;
	while (gap > 1 || swap)
	{
		gap = (gap * 10) / 13;
		if (gap == 9 || gap == 10)
			gap = 11;
		if (gap < 1)
			gap = 1;
		swap = ft_swap(order, dist, amount, gap);
	}
}
