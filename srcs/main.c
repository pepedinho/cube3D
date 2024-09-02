/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:46:00 by itahri            #+#    #+#             */
/*   Updated: 2024/09/02 17:17:50 by madamou          ###   ########.fr       */
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
	printf_input(&data);
	check_map(&data);
	printf("spawn position : (x : %d , y : %d)\n", data.p_pos.x, data.p_pos.y);
	trace_perimeter(&data, 2);
	return (0);
}
