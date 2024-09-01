/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:46:00 by itahri            #+#    #+#             */
/*   Updated: 2024/09/01 14:06:53 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	main(int argc, char *argv[])
{
	t_map_data	*data;

	data = get_map_data(argv[argc - 1]);
	if (!data)
		printf("NO DATA FOUD");
	else
	{
		printf("S = %s\n", data->tx_south);
		printf("N = %s\n", data->tx_north);
		printf("E = %s\n", data->tx_east);
		printf("W = %s\n", data->tx_west);
		printf("C = %s\n", data->tx_ceiling);
		printf("F = %s\n", data->tx_floor);
	};
	return (0);
}
