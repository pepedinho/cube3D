/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:04:46 by itahri            #+#    #+#             */
/*   Updated: 2024/09/07 14:24:41 by itahri           ###   ########.fr       */
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

/*
 * 0 = floor
 * 1 = wall
 * (N-S-E-W) = player spawn point and cardinal direction
 */

/*
 * b_x & b_y = x and y pos in orhtogonal buffer

	* r_x & r_y = x and y pos in mlx render when r_x = 2.0 b_x = 2 but when r_x = 1.9 b_x still egal to 1
 */
typedef struct s_coord
{
	int		b_x;
	int		b_y;
	double	r_x;
	double	r_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_coord;

typedef struct s_input
{
	char	*tx_north;
	char	*tx_south;
	char	*tx_east;
	char	*tx_west;
	char	*tx_floor;
	char	*tx_ceiling;
}			t_input;

typedef struct s_mlx
{
	int		width;
	int		height;
	char *adrr;
	int  size_line;
	int 	bits_per_pixel;
	int		endiant;
	void	*init;
	void	*window;
	void	*white_i;
	void	*black_i;
	void *wall_i;
}			t_mlx;

typedef struct s_map_data
{
	t_input	input;
	t_mlx	*mlx;
	char	*map_path;
	t_coord	p_pos;
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
