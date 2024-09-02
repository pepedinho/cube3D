/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:54:14 by itahri            #+#    #+#             */
/*   Updated: 2024/09/02 17:53:57 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycatsing.h"

void	define_fov(t_map_data *map_data, int r)
{
	double	radiant;
	double	alpha;
	double	x1;
	double	x2;
	double	y1;
	double	y2;

	alpha = 0;
	radiant = 80 * M_PI / 180;
	x1 = map_data->p_pos.x + r * cos(alpha);
	y1 = map_data->p_pos.y + r * sin(alpha);
	x2 = map_data->p_pos.x + r * cos(alpha + radiant);
	y2 = map_data->p_pos.y + r * sin(alpha + radiant);
}

int	trace_perimeter(t_map_data *map_data, int r)
{
	double	h;
	double	k;
	double	radiant;
	int		i;

	i = 0;
	while (i < 50)
	{
		radiant = 2 * M_PI * i / 50;
		h = map_data->p_pos.x + r * cos(radiant);
		k = map_data->p_pos.y + r * sin(radiant);
		printf("point in : (%f, %f)\n", h, k);
		i++;
	}
	return (1);
}
