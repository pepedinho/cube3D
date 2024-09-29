/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 03:21:13 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 03:26:31 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	string_put(t_map_data *data, size_t fps)
{
	char	*str;

	str = ft_sprintf("fps = %d", fps);
	if (!str)
		destroy_mlx(data);
	mlx_string_put(data->mlx.init, data->mlx.window, 1800, 50, WHITE, str);
	if (data->door_trigger && data->map[data->door_y][data->door_x] == 'D')
		mlx_string_put(data->mlx.init, data->mlx.window, 900, 900, 0XFFFFF,
			"press space to open the door");
	else if (data->door_trigger && data->map[data->door_y][data->door_x] == 'O')
		mlx_string_put(data->mlx.init, data->mlx.window, 900, 900, 0XFFFFF,
			"press space to close the door");
	free(str);
}

static void	update_fps_and_enemies(t_map_data *data, size_t *frame_count, size_t *fps, long long *frame_enemies)
{
	*fps = *frame_count;
	*frame_count = 0;
	(*frame_enemies)++;
	if (*frame_enemies >= data->mlx.enemy.spawn)
	{
		*frame_enemies = 0;
		random_enemies(data);
	}
}

static void	render_to_screen(t_map_data *data)
{
	(raycasting(data), display_gun(data, data->mlx.gun));
	display_crosshair(data);
	mlx_put_image_to_window(data->mlx.init, data->mlx.window,
		data->mlx.img.img, 0, 0);
}

int	render(t_map_data *data)
{
	static time_t		last_time;
	struct timeval		current_time;
	static size_t		frame_count;
	static size_t		fps;
	static long long	frame_enemies;
	static int			cnt;

	(mouse_movement(data), change_player(data));
	if (data->mlx.window != NULL)
	{
		data->door_trigger = 0;
		render_to_screen(data);
		handle_gun_fire(data, &cnt);
		gettimeofday(&current_time, NULL);
		if (current_time.tv_sec > last_time)
		{
			update_fps_and_enemies(data, &frame_count, &fps, &frame_enemies);
			last_time = current_time.tv_sec;
		}
		(string_put(data, fps), trace_perimeter(data, 5));
	}
	frame_count++;
	return (1);
}