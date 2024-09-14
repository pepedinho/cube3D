/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:54:18 by madamou           #+#    #+#             */
/*   Updated: 2024/09/14 20:55:08 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

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
