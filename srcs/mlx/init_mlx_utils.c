/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 04:01:02 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 04:01:54 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

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
	printf("Image properties(%s): width=%d, height=%d, bpp=%d, size_line=%d\n",
		img->path, img->width, img->height, img->bits_per_pixel,
		img->size_line);
	img->bits_per_pixel_div8 = img->bits_per_pixel / 8;	
}

void	new_image(t_map_data *data, t_img *img)
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
	img->bits_per_pixel_div8 = img->bits_per_pixel / 8;
}

void	path_to_mlx_img(t_map_data *data, t_mlx *mlx)
{
	mlx->wall[N].path = data->input.tx_north;
	mlx->wall[S].path = data->input.tx_south;
	mlx->wall[E].path = data->input.tx_east;
	mlx->wall[W].path = data->input.tx_west;
	mlx->white.path = WHITE_I;
	mlx->dot.path = DOT;
	mlx->blue.path = BLUE;
	mlx->gun.path = GUN;
	mlx->shoot[0].path = SHOOT_1;
	mlx->shoot[1].path = SHOOT_2;
	mlx->door.path = DOOR;
	mlx->enemy.img.path = ENEMY;
}