/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:58:27 by madamou           #+#    #+#             */
/*   Updated: 2024/10/01 16:23:56 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"
#include "minilibx.h"
#include "sprites/sprites.h"
#include <X11/X.h>
#include <stdio.h>

void	ft_mlx_destroy_image(void *mlx_ptr, void *img)
{
	if (img)
		mlx_destroy_image(mlx_ptr, img);
}

void	destroy_mlx(t_map_data *data)
{
	t_mlx	mlx;

	mlx = data->mlx;
	if (mlx.window)
		mlx_destroy_window(mlx.init, mlx.window);
	ft_free_2d(data->map);
	ft_mlx_destroy_image(mlx.init, mlx.wall[N].img);
	ft_mlx_destroy_image(mlx.init, mlx.wall[S].img);
	ft_mlx_destroy_image(mlx.init, mlx.wall[E].img);
	ft_mlx_destroy_image(mlx.init, mlx.wall[W].img);
	ft_mlx_destroy_image(mlx.init, mlx.dot.img);
	ft_mlx_destroy_image(mlx.init, mlx.gun.img);
	ft_mlx_destroy_image(mlx.init, mlx.shoot[0].img);
	ft_mlx_destroy_image(mlx.init, mlx.shoot[1].img);
	ft_mlx_destroy_image(mlx.init, mlx.enemy.img.img);
	ft_mlx_destroy_image(mlx.init, mlx.blue.img);
	ft_mlx_destroy_image(mlx.init, mlx.white.img);
	ft_mlx_destroy_image(mlx.init, mlx.door.img);
	ft_mlx_destroy_image(mlx.init, mlx.img.img);
	if (mlx.init)
		(mlx_destroy_display(mlx.init), free(mlx.init));
	(free(data->input.tx_north), free(data->input.tx_south));
	(free(data->input.tx_east), free(data->input.tx_west));
	(free(data->input.tx_ceiling), free(data->input.tx_floor));
	(free_all_sprite(data->sprites), exit(EXIT_SUCCESS));
}

void	mlx_hook_setup(t_map_data *data, t_mlx mlx)
{
	mlx_mouse_move(mlx.init, mlx.window, mlx.width_div2, mlx.height_div2);
	mlx_mouse_hide(mlx.init, mlx.window);
	mlx_loop_hook(mlx.init, render, data);
	mlx_hook(mlx.window, KeyPress, KeyPressMask, key_prees, data);
	mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_mouse_hook(mlx.window, mouse_click, data);
	mlx_hook(mlx.window, 17, 0L, click_cross, data);
	mlx_loop(mlx.init);
}

void	open_all_images(t_map_data *data, t_mlx *mlx)
{
	new_image(data, &mlx->img);
	ft_init_img(data, &mlx->wall[N]);
	ft_init_img(data, &mlx->wall[S]);
	ft_init_img(data, &mlx->wall[E]);
	ft_init_img(data, &mlx->wall[W]);
	ft_init_img(data, &mlx->shoot[0]);
	ft_init_img(data, &mlx->shoot[1]);
	ft_init_img(data, &mlx->door);
	ft_init_img(data, &mlx->white);
	ft_init_img(data, &mlx->blue);
	ft_init_img(data, &mlx->dot);
	ft_init_img(data, &mlx->gun);
	ft_init_img(data, &mlx->enemy.img);
}

int	init_mlx(t_map_data *data)
{
	t_mlx	mlx;

	srand(time(NULL));
	ft_memset(&mlx, 0, sizeof(mlx));
	mlx.init = mlx_init();
	if (!mlx.init)
		return (destroy_mlx(data), 0);
	path_to_mlx_img(data, &mlx);
	mlx_get_screen_size(mlx.init, &mlx.width, &mlx.height);
	if (mlx.width > 1920)
		mlx.width = 1920;
	if (mlx.height > 1080)
		mlx.height = 1080;
	mlx.width_div2 = mlx.width / 2;
	mlx.height_div2 = mlx.height / 2;
	mlx.window = mlx_new_window(mlx.init, mlx.width, mlx.height, "cub3D");
	if (!mlx.window)
		return (destroy_mlx(data), 0);
	data->mlx = mlx;
	data->key.mouse_hide = true;
	mlx.enemy.spawn = 1;
	open_all_images(data, &data->mlx);
	data->key.speed_boost = 0;
	mlx_hook_setup(data, mlx);
	return (1);
}
