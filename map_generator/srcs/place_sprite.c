/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:12:01 by madamou           #+#    #+#             */
/*   Updated: 2024/09/07 15:51:55 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_generator.h"

void	ft_place_player(char **map, int x, int y)
{
	int	player_x;
	int	player_y;
	int orientation;

	player_x = 0;
	player_y = 0;
	orientation = 0;
	while (player_x == 0)
		player_x = rand() % (x - 1);
	while (player_y == 0)
		player_y = rand() % (y - 1);
	orientation = rand() % 4;
	if (orientation == 0)
		map[player_y][player_x] = 'N';
	else if (orientation == 1)
		map[player_y][player_x] = 'E';
	else if (orientation == 2)
		map[player_y][player_x] = 'S';
	else if (orientation == 3)
		map[player_y][player_x] = 'W';
}

void	ft_place_collectibles(char **map, int x, int y, int coins)
{
	int	coins_x;
	int	coins_y;
	int	i;

	i = 0;
	while (i < coins)
	{
		coins_x = 0;
		coins_y = 0;
		while (coins_x == 0)
			coins_x = rand() % (x - 1);
		while (coins_y == 0)
			coins_y = rand() % (y - 1);
		if (map[coins_y][coins_x] == '0')
		{
			map[coins_y][coins_x] = 'C';
			i++;
		}
	}
}

void	ft_place_exit(char **map, int x, int y)
{
	int	exit_x;
	int	exit_y;
	int	i;

	i = 0;
	while (i < 1)
	{
		exit_x = 0;
		exit_y = 0;
		while (exit_x == 0)
			exit_x = rand() % (x - 1);
		while (exit_y == 0)
			exit_y = rand() % (y - 1);
		if (map[exit_y][exit_x] == '0')
		{
			map[exit_y][exit_x] = 'E';
			i++;
		}
	}
}
