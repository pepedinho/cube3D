/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:27:22 by madamou           #+#    #+#             */
/*   Updated: 2024/10/01 14:42:58 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

int	check_map_char_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_is_in_charset(line[i++], " 01NSEWD"))
			return (0);
	}
	return (1);
}

int	check_only_one_player(char *line)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (line[i])
	{
		if (ft_is_in_charset(line[i++], "NSEW"))
			cpt++;
	}
	return (cpt);
}

int	check_map(t_map_data *data)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (data->map[i])
	{
		player += check_only_one_player(data->map[i]);
		if (!check_map_char_line(data->map[i++]))
		{
			ft_putstr_fd("Error\nChar not good at line \n", 2);
			destroy_mlx(data);
			return (0);
		}
	}
	if (player == 0)
		ft_putstr_fd("Error\nNo player\n", 2);
	if (player > 1)
		ft_putstr_fd("Error\nToo many players\n", 2);
	if (player != 1)
		return (destroy_mlx(data), 0);
	return (check_map_playable(data));
}
