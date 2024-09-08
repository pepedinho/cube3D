/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:58:27 by madamou           #+#    #+#             */
/*   Updated: 2024/09/08 19:16:55 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

void	destroy_mlx(t_map_data *data)
{
	t_mlx	mlx;

	mlx = data->mlx;
	if (mlx.window)
		mlx_destroy_window(mlx.init, mlx.window);
	ft_free_2d(data->map);
	mlx_destroy_image(mlx.init, mlx.wall[N].img);
	mlx_destroy_image(mlx.init, mlx.wall[S].img);
	mlx_destroy_image(mlx.init, mlx.wall[E].img);
	mlx_destroy_image(mlx.init, mlx.wall[W].img);
	mlx_destroy_display(mlx.init);
	free(mlx.init);
	free(data->input.tx_north);
	free(data->input.tx_south);
	free(data->input.tx_east);
	free(data->input.tx_west);
	free(data->input.tx_ceiling);
	free(data->input.tx_floor);
	exit(EXIT_SUCCESS);
}

void	ft_init_img(t_map_data *data, t_img *img)
{
	img->img = mlx_xpm_file_to_image(data->mlx.init, img->path, &img->width,
			&img->height);
	if (!img->img)
	{
		ft_printf("Error with image loading\n");
		destroy_mlx(data);
	}
	img->adrr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->size_line, &img->endiant);
	if (!img->adrr)
	{
		ft_printf("Error when trying to get image data\n");
		destroy_mlx(data);
	}
}

void new_image(t_map_data *data, t_img *img)
{
	img->img = mlx_new_image(data->mlx.init, data->mlx.width, data->mlx.height);
	if (!img->img)
	{
		ft_printf("Error with image loading\n");
		destroy_mlx(data);
	}
	img->adrr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->size_line, &img->endiant);
	if (!img->adrr)
	{
		ft_printf("Error when trying to get image data\n");
		destroy_mlx(data);
	}
}

void	path_to_mlx_img(t_map_data *data, t_mlx *mlx)
{
	mlx->wall[N].path = data->input.tx_north;
	mlx->wall[S].path = data->input.tx_south;
	mlx->wall[E].path = data->input.tx_east;
	mlx->wall[W].path = data->input.tx_west;
}

int	init_mlx(t_map_data *data)
{
	t_mlx	mlx;

	mlx.init = mlx_init();
	if (!mlx.init)
		return (destroy_mlx(data), 0);
	path_to_mlx_img(data, &mlx);
	mlx_get_screen_size(mlx.init, &mlx.width, &mlx.height);
	if (mlx.width > 1920)
		mlx.width = 1920;
	if (mlx.height > 1080)
		mlx.height = 1080;
	mlx.window = mlx_new_window(mlx.init, mlx.width, mlx.height, "cub3D");
	if (!mlx.window)
		return (destroy_mlx(data), 0);
	data->mlx = mlx;
	new_image(data, &mlx.img);
	ft_init_img(data, &mlx.wall[N]);
	ft_init_img(data, &mlx.wall[S]);
	ft_init_img(data, &mlx.wall[E]);
	ft_init_img(data, &mlx.wall[W]);
	data->mlx = mlx;
	mlx_loop_hook(mlx.init, render, data);
	mlx_hook(mlx.window, 17, 0L, click_cross, data);
	mlx_hook(mlx.window, 2, 1L << 0, handle_input, data);
	mlx_loop(mlx.init);
	return (1);
}
