/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:04:46 by itahri            #+#    #+#             */
/*   Updated: 2024/09/01 22:43:12 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define NO 20
# define SO 21
# define EA 22
# define WE 23
# define F 24
# define C 25

# ifdef CUBE3D_H
#  undef CUBE3D_H
# endif

# include "../../includes/cube3D.h"

/*
 * 0 = floor
 * 1 = wall
 * (N-S-E-W) = player spawn point and cardinal direction
 */

typedef struct s_map_data
{
	char	*tx_north;
	char	*tx_south;
	char	*tx_east;
	char	*tx_west;
	char	*tx_floor;
	char	*tx_ceiling;
	char	*map_path;
	char	**map;
}			t_map_data;

// parsing
t_map_data	*get_map_data(char *filename, t_map_data *data);

// map_parsing
int			get_map(t_map_data *map_data, char *line, int fd);

// utils
int			ft_isspace(char c);

// checking
int			check_map(t_map_data *data);
int			check_map_playable(t_map_data *data);
int			flood_fill(t_map_data *data);

#endif
