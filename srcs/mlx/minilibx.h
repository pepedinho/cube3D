/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:15:47 by madamou           #+#    #+#             */
/*   Updated: 2024/09/04 12:59:27 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_H
# define MINILIBX_H

# include <X11/keysym.h>

# define WIDTH 32
# define HEIGHT 32
# define WIDTH_X2 64
# define HEIGHT_X2 64
# define WHITE_I "assets/white_tile.xpm"
# define BLACK_I "assets/black_tile.xpm"

# ifdef CUBE3D_H
#  undef CUBE3D_H
# endif

typedef struct s_map_data	t_map_data;

int							init_mlx(t_map_data *data);
void						destroy_mlx(t_map_data *data);

#endif
