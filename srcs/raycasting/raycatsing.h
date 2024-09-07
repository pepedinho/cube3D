/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:56:24 by itahri            #+#    #+#             */
/*   Updated: 2024/09/07 19:25:56 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# ifdef CUBE3D_H
#  undef CUBE3D_H
# endif

# include "../../includes/cube3D.h"

// typedef struct s_map_data	t_map_data;

// raycast
int							trace_perimeter(t_map_data *map_data, int r,
								double alpha);
int							find_r(t_map_data *map_data);
double						abs_value(double nb);


// utils
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue);

// mini map
void						render_map(t_map_data *map_data);
void raycasting(t_map_data *data);

#endif
