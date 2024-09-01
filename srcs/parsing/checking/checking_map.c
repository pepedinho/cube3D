/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:27:22 by madamou           #+#    #+#             */
/*   Updated: 2024/09/01 22:21:10 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

int	check_map_char_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_is_in_charset(line[i++], " 01NSEW"))
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
			ft_fprintf(2, "Error\nChar not good at line %d\n", i);
			return (0);
		}
	}
	if (player == 0)
		ft_fprintf(2, "Error\nNo player\n");
	if (player > 1)
		ft_fprintf(2, "Error\nToo many players (%d players)\n", player);
	if (player != 1)
		return (0);
	return (flood_fill(data));
}
