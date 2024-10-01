/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:46:00 by itahri            #+#    #+#             */
/*   Updated: 2024/10/01 14:34:09 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"
#include <stdio.h>

void	print_2d_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		printf("%s\n", tab[i++]);
}

int	check_input(t_map_data *data)
{
	if (data->input.tx_south && data->input.tx_north && data->input.tx_east
		&& data->input.tx_east && data->input.tx_west && data->input.tx_ceiling
		&& data->input.tx_floor)
		return (1);
	free(data->input.tx_south);
	free(data->input.tx_north);
	free(data->input.tx_east);
	free(data->input.tx_west);
	free(data->input.tx_ceiling);
	free(data->input.tx_floor);
	ft_free_2d(data->map);
	return (0);
}

void	e_w(t_map_data *data)
{
	int	y;
	int	x;

	x = data->p_pos.r_x;
	y = data->p_pos.r_y;
	if (data->map[y][x] == 'E')
	{
		data->p_pos.dir_x = 1;
		data->p_pos.dir_y = 0;
		data->p_pos.plane_x = 0;
		data->p_pos.plane_y = 0.66;
	}
	else if (data->map[y][x] == 'W')
	{
		data->p_pos.dir_x = -1;
		data->p_pos.dir_y = 0;
		data->p_pos.plane_x = 0;
		data->p_pos.plane_y = -0.66;
	}
}

void	set_player_angle(t_map_data *data)
{
	int	y;
	int	x;

	x = data->p_pos.r_x;
	y = data->p_pos.r_y;
	if (data->map[y][x] == 'N')
	{
		data->p_pos.dir_x = 0;
		data->p_pos.dir_y = -1;
		data->p_pos.plane_x = 0.66;
		data->p_pos.plane_y = 0;
	}
	else if (data->map[y][x] == 'S')
	{
		data->p_pos.dir_x = 0;
		data->p_pos.dir_y = 1;
		data->p_pos.plane_x = -0.66;
		data->p_pos.plane_y = 0;
	}
	e_w(data);
}

int	main(int argc, char *argv[])
{
	t_map_data	data;

	if (argc != 2)
	{
		ft_printf("Bad arguments number: <map_path>\n");
		return (1);
	}
	ft_memset(&data, 0, sizeof(data));
	if (!get_map_data(argv[argc - 1], &data))
		return (1);
	if (!check_input(&data))
		return (1);
	if (check_map(&data) == 0)
		return (1);
	set_player_angle(&data);
	init_mlx(&data);
	return (0);
}
