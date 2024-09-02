/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:54:14 by itahri            #+#    #+#             */
/*   Updated: 2024/09/02 16:58:17 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycatsing.h"

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
