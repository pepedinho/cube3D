/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:58:27 by madamou           #+#    #+#             */
/*   Updated: 2024/09/04 13:06:26 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"
#include <stdio.h>

int	click_cross(t_map_data *data)
{
	destroy_mlx(data);
	return (1);
}

void	moove_fov(t_map_data *data, double alpha)
{
	printf("------| a : %f | p_x : %f | p_y : %f |------\n", alpha,
		data->p_pos.r_x, data->p_pos.r_y);
	render_map(data);
	trace_perimeter(data, 1, alpha);
}

int	is_same(double prev, double curr)
{
	int	prev_int;
	int	curr_int;

	prev_int = (int)floor(prev);
	curr_int = (int)floor(curr);
	if (prev_int != curr_int)
		return (1);
	printf("/!\\debug/!\\ prev_int : %d | curr_int : %d\n", prev_int, curr_int);
	return (0);
}

double	x_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '1')
		i++;
	printf("/!\\debug/!\\ x_len : %d\n\tline : %s\n", i, line);
	return ((double)i);
}

void	moov(t_map_data *data, double alpha, int key)
{
	double	n_pos;

	printf("------| a : %f | p_x(r) : %f | p_y(r) : %f |------\n", alpha,
		data->p_pos.r_x, data->p_pos.r_y);
	printf("//////| a : %f | p_x(b) : %d | p_y(b) : %d |\\\\\\\\\\\\\n", alpha,
		data->p_pos.b_x, data->p_pos.b_y);
	if (key == XK_q)
	{
		n_pos = data->p_pos.r_x - 0.1;
		if (n_pos < 0.0)
			return ;
		if (is_same(data->p_pos.r_x, n_pos)
			&& data->map[data->p_pos.b_y][data->p_pos.b_x - 1] == '1')
			return ;
		if (is_same(data->p_pos.r_x, n_pos))
			data->p_pos.b_x -= 1;
		data->p_pos.r_x = n_pos;
	}
	else if (key == XK_d)
	{
		n_pos = data->p_pos.r_x + 0.1;
		if (n_pos > ft_strlen(data->map[data->p_pos.b_y]))
			return ;
		if (is_same(data->p_pos.r_x, n_pos)
			&& data->map[data->p_pos.b_y][data->p_pos.b_x + 1] == '1')
			return ;
		if (is_same(data->p_pos.r_x, n_pos))
			data->p_pos.b_x += 1;
		data->p_pos.r_x = n_pos;
	}
	else if (key == XK_z)
	{
		n_pos = data->p_pos.r_y - 0.1;
		if (n_pos < 0.0)
			return ;
		if (is_same(data->p_pos.r_y, n_pos) && data->map[data->p_pos.b_y
			- 1][data->p_pos.b_x] == '1')
			return ;
		if (is_same(data->p_pos.r_y, n_pos))
			data->p_pos.b_y -= 1;
		data->p_pos.r_y = n_pos;
	}
	else if (key == XK_s)
	{
		n_pos = data->p_pos.r_y + 0.1;
		if (is_same(data->p_pos.r_y, n_pos)
			&& data->map[(int)floor(n_pos)][data->p_pos.b_x] == '1')
			return ;
		if (is_same(data->p_pos.r_y, n_pos))
			data->p_pos.b_y += 1;
		data->p_pos.r_y = n_pos;
	}
	render_map(data);
	trace_perimeter(data, 1, alpha);
}

void	destroy_mlx(t_map_data *data)
{
	t_mlx	*mlx;

	mlx = data->mlx;
	if (mlx->window)
		mlx_destroy_window(mlx->init, mlx->window);
	mlx_destroy_display(mlx->init);
	free(mlx->init);
	free(mlx);
	exit(EXIT_SUCCESS);
}

int	handle_input(int keysym, t_map_data *data)
{
	static double	alpha = 0;

	if (keysym == XK_Escape)
		destroy_mlx(data);
	if (keysym == XK_Left)
	{
		if (alpha > 6.4)
			alpha = 0;
		moove_fov(data, alpha);
		alpha += 0.1;
	}
	else if (keysym == XK_Right)
	{
		if (alpha < 0)
			alpha = 6.4;
		moove_fov(data, alpha);
		alpha -= 0.1;
	}
	else if (keysym == XK_q)
		moov(data, alpha, XK_q);
	else if (keysym == XK_d)
		moov(data, alpha, XK_d);
	else if (keysym == XK_z)
		moov(data, alpha, XK_z);
	else if (keysym == XK_s)
		moov(data, alpha, XK_s);
	return (1);
}

int	init_img(t_map_data *map_data)
{
	int	img_width;
	int	img_height;

	img_width = WIDTH;
	img_height = HEIGHT;
	map_data->mlx->white_i = NULL;
	map_data->mlx->black_i = NULL;
	map_data->mlx->white_i = mlx_xpm_file_to_image(map_data->mlx->init, WHITE_I,
			&img_width, &img_height);
	if (!map_data->mlx->white_i)
		return (printf("Error with image loading\n"), 0);
	map_data->mlx->black_i = mlx_xpm_file_to_image(map_data->mlx->init, BLACK_I,
			&img_width, &img_height);
	if (!map_data->mlx->black_i)
		return (printf("Error with image loading\n"), 0);
	return (1);
}

int	init_mlx(t_map_data *data)
{
	t_mlx	*mlx;

	data->mlx = malloc(sizeof(t_mlx));
	if (!data->mlx)
		return (0);
	mlx = data->mlx;
	// ft_memset(mlx, 0, sizeof(mlx));
	mlx->init = mlx_init();
	if (!mlx->init)
		return (destroy_mlx(data), 0);
	// mlx_get_screen_size(mlx->init, &mlx->width, &mlx->height);
	mlx->width = 1280;
	mlx->height = 720;
	mlx->window = mlx_new_window(mlx->init, mlx->width, mlx->height, "cube3D");
	if (!mlx->window)
		return (destroy_mlx(data), 0);
	init_img(data);
	render_map(data);
	mlx_hook(mlx->window, 17, 0L, click_cross, data);
	mlx_hook(mlx->window, 2, 1L << 0, handle_input, data);
	mlx_loop(mlx->init);
	return (1);
}
