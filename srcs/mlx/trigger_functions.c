/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:30:52 by itahri            #+#    #+#             */
/*   Updated: 2024/09/08 18:53:22 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

int	click_cross(t_map_data *data)
{
	destroy_mlx(data);
	return (1);
}

int	handle_input(int keysym, t_map_data *data)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;
	double	move_speed;

	move_speed = 0.1;
	rot_speed = 0.05;
	old_dir_x = 0;
	old_plane_x = 0;
	if (keysym == XK_Escape)
		destroy_mlx(data);
	if (keysym == XK_Right)
		right_fov(data, old_dir_x, rot_speed, old_plane_x);
	else if (keysym == XK_Left)
		left_fov(data, old_dir_x, rot_speed, old_plane_x);
	else if (keysym == XK_w || keysym == XK_z)
		forward(data, move_speed);
	else if (keysym == XK_s)
		behind(data, move_speed);
	else if (keysym == XK_d)
		right(data, move_speed);
	else if (keysym == XK_q || keysym == XK_a)
		left(data, move_speed);
	return (1);
}

int render(t_map_data *data)
{
    static time_t last_time = 0;
    struct timeval current_time;
    static size_t frame_count = 0;
    static size_t fps = 0;
    
    if (data->mlx.window != NULL)
    {
        raycasting(data);
		mlx_put_image_to_window(data->mlx.init, data->mlx.window, data->mlx.img.img, 0, 0);
        gettimeofday(&current_time, NULL);
        if (current_time.tv_sec > last_time)
        {
            fps = frame_count;
            frame_count = 0;
            last_time = current_time.tv_sec;
        }
        mlx_string_put(data->mlx.init, data->mlx.window, 1800, 50, 0XFFFFFF, ft_sprintf("fps = %d", fps));
    }
    frame_count++;
    return (1);
}

