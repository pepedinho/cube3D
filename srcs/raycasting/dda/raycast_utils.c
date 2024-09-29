/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:20:19 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 05:25:14 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

int	sign(double nb)
{
	if (nb < 0)
		return (-1);
	return (1);
}

double	set_side_dist(double ray_dir, double pos, int map, double delta)
{
	if (ray_dir < 0)
		return ((pos - map) * delta);
	return ((map + 1.0 - pos) * delta);
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red * 256 * 256 + green * 256 + blue);
}

double	set_deltadist(double raydir)
{
	if (raydir == 0)
		return (INFINITY);
	return (fabs(1 / raydir));
}
