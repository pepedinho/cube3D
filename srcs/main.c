/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:46:00 by itahri            #+#    #+#             */
/*   Updated: 2024/09/01 19:04:32 by madamou          ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	t_map_data	data;

	ft_memset(&data, 0, sizeof(data));
	get_map_data(argv[argc - 1], &data);
	printf("S = %s\n", data.tx_south);
	printf("N = %s\n", data.tx_north);
	printf("E = %s\n", data.tx_east);
	printf("W = %s\n", data.tx_west);
	printf("C = %s\n", data.tx_ceiling);
	printf("F = %s\n", data.tx_floor);
	print_2d_array(data.map);
	return (0);
}
