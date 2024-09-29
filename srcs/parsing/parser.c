/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:12:58 by itahri            #+#    #+#             */
/*   Updated: 2024/09/29 04:32:25 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"
#include <stdio.h>

// TODO check if no space between type and path

int	is_full_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atouc(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result = result + (str[i] - '0');
		if (result > 255)
			return (-1);
		i++;
	}
	return (result);
}

int	check_rgb_floor_ceiling(t_map_data *data)
{
	char	**rgb[2];
	int		i;

	rgb[0] = ft_split(data->input.tx_floor, ",");
	rgb[1] = ft_split(data->input.tx_ceiling, ",");
	if (!rgb[0] || !rgb[1])
		return (ft_free_2d(rgb[0]), ft_free_2d(rgb[1]), 0);
	if (ft_strlen_2d(rgb[0]) != 3 || ft_strlen_2d(rgb[0]) != 3)
		return (ft_free_2d(rgb[0]), ft_free_2d(rgb[1]), 0);
	i = 0;
	while (i <= 1)
	{
		if (!is_full_digit(rgb[i][0]) || !is_full_digit(rgb[i][1]) || !is_full_digit(rgb[i][2]))
			return (ft_free_2d(rgb[0]), ft_free_2d(rgb[1]), 0);
		if (ft_atouc(rgb[i][0]) == -1 || ft_atouc(rgb[i][1]) == -1 || ft_atouc(rgb[i][2]) == -1)
			return (ft_free_2d(rgb[0]), ft_free_2d(rgb[1]), 0);
		if (i == 0)
			data->input.floor_color = encode_rgb(ft_atouc(rgb[i][0]),
			ft_atouc(rgb[i][1]), ft_atouc(rgb[i][2]));
		else
			data->input.ceiling_color = encode_rgb(ft_atouc(rgb[i][0]),
		ft_atouc(rgb[i][1]), ft_atouc(rgb[i][2]));
		i++;
	}
	return (ft_free_2d(rgb[0]), ft_free_2d(rgb[1]), 1);
}

t_map_data	*get_map_data(char *filename, t_map_data *map_data)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, fd, map_data);
		line = get_next_line(fd);
	}
	close(fd);
	if (check_rgb_floor_ceiling(map_data) == 0)
	{
		ft_free_2d(map_data->map);
		free(map_data->input.tx_ceiling);
		free(map_data->input.tx_floor);
		free(map_data->input.tx_north);
		free(map_data->input.tx_south);
		(free(map_data->input.tx_east), free(map_data->input.tx_west));
		printf("Erreur\n RGB not good\n");
		exit(EXIT_FAILURE);
	}
	return (map_data);
}
