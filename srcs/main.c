/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:46:00 by itahri            #+#    #+#             */
/*   Updated: 2024/09/02 13:29:20 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	print_2d_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		printf("%s\n", tab[i++]);
}

void	printf_input(t_map_data *data)
{
	printf("S = %s\n", data->input.tx_south);
	printf("N = %s\n", data->input.tx_north);
	printf("E = %s\n", data->input.tx_east);
	printf("W = %s\n", data->input.tx_west);
	printf("C = %s\n", data->input.tx_ceiling);
	printf("F = %s\n", data->input.tx_floor);
	print_2d_array(data->map);
}

int	main(int argc, char *argv[])
{
	t_map_data	data;

	ft_memset(&data, 0, sizeof(data));
	get_map_data(argv[argc - 1], &data);
	printf_input(&data);
	check_map(&data);
	printf("spawn position : (x : %d , y : %d)\n", data.p_pos.x, data.p_pos.y);
	init_mlx(&data);
	//destroy_mlx(&data.mlx);
	return (0);
}
