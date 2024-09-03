/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:58:27 by madamou           #+#    #+#             */
/*   Updated: 2024/09/02 17:29:01 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"
#include <stdio.h>

int	click_cross(t_map_data *data)
{
	destroy_mlx(data);
	return (1);
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
	if (keysym == XK_d)
	{
		printf("-----------------------------%f------------------------------\n",
			alpha);
		trace_perimeter(data, 2, alpha);
		alpha += 0.1;
	}
	return (1);
}

int	init_mlx(t_map_data *data)
{
	t_mlx	*mlx;

	data->mlx = malloc(sizeof(data->mlx));
	if (!data->mlx)
		return (0);
	mlx = data->mlx;
	ft_memset(mlx, 0, sizeof(mlx));
	mlx->init = mlx_init();
	if (!mlx->init)
		return (destroy_mlx(data), 0);
	mlx_get_screen_size(mlx->init, &mlx->width, &mlx->height);
	mlx->window = mlx_new_window(mlx->init, mlx->width, mlx->height, "cube3D");
	if (!mlx->window)
		return (destroy_mlx(data), 0);
	mlx_hook(mlx->window, 17, 0L, click_cross, data);
	mlx_key_hook(mlx->window, handle_input, data);
	mlx_loop(mlx->init);
	return (1);
}
