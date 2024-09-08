/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:34:01 by itahri            #+#    #+#             */
/*   Updated: 2024/09/08 19:54:50 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../srcs/parsing/parsing.h"
# include "../minilibx-linux/mlx.h"
# include "../srcs/mlx/minilibx.h"
# include "../srcs/raycasting/raycatsing.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
#include <sys/time.h>

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

void	print_2d_array(char **tab);

#endif
