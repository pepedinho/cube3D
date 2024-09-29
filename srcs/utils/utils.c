/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:54:18 by madamou           #+#    #+#             */
/*   Updated: 2024/09/28 23:39:29 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	swap_double(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

double	rand_value(double min, double max)
{
	double	range;
	double	div;

	range = (max - min);
	div = RAND_MAX / range;
	return (min + (rand() / div));
}

int	get_map_height(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

double	distance_euclid(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
