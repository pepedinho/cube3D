/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:12:58 by itahri            #+#    #+#             */
/*   Updated: 2024/09/07 19:06:03 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

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
	char	**rgb;
	int		i;
	int		tab[3];

	rgb = ft_split(data->input.tx_floor, ",");
	if (!rgb)
		return (0);
	i = 0;
	while (rgb[i])
	{
		if (i == 3)
			return (ft_free_2d(rgb), 0);
		if (is_full_digit(rgb[i]) == 0)
			return (ft_free_2d(rgb), 0);
		tab[i] = ft_atouc(rgb[i]);
		if (tab[i++] == -1)
			return (ft_free_2d(rgb), 0);
	}
	data->input.floor_color = encode_rgb(tab[0], tab[1], tab[2]);
	ft_free_2d(rgb);
	rgb = ft_split(data->input.tx_ceiling, ",");
	if (!rgb)
		return (0);
	i = 0;
	while (rgb[i])
	{
		if (i == 3)
			return (ft_free_2d(rgb), 0);
		if (is_full_digit(rgb[i]) == 0)
			return (ft_free_2d(rgb), 0);
		tab[i] = ft_atouc(rgb[i]);
		if (tab[i++] == -1)
			return (ft_free_2d(rgb), 0);
	}
	data->input.ceiling_color = encode_rgb(tab[0], tab[1], tab[2]);
	ft_free_2d(rgb);
	return (1);
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
	check_rgb_floor_ceiling(map_data);
	return (map_data);
}
