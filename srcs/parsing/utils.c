/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:35:54 by itahri            #+#    #+#             */
/*   Updated: 2024/10/01 16:26:49 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	check_type(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (0);
	if (line[i] == '\n')
		return (0);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		return (NO);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (SO);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (EA);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (WE);
	else if (line[i] == 'F')
		return (F);
	else if (line[i] == 'C')
		return (C);
	return (1);
}

void	assign_path(char *path, t_map_data *map_data, int type)
{
	if (type == NO)
		map_data->input.tx_north = path;
	else if (type == SO)
		map_data->input.tx_south = path;
	else if (type == WE)
		map_data->input.tx_west = path;
	else if (type == EA)
		map_data->input.tx_east = path;
	else if (type == F)
		map_data->input.tx_floor = path;
	else if (type == C)
		map_data->input.tx_ceiling = path;
}

int	get_path(char *line, t_map_data *map_data, int type)
{
	int		i;
	char	*path;

	i = 0;
	if (type == 0 || type == 1)
		return (0);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (type == F || type == C)
		i++;
	else
		i += 2;
	while (line[i] && ft_isspace(line[i]))
		i++;
	path = ft_substr(line, i, ft_strlen(line + i) - 1);
	if (!path)
		return (0);
	return (assign_path(path, map_data, type), 1);
}

void	parse_line(char *line, int fd, t_map_data *map_data)
{
	if (!get_path(line, map_data, check_type(line)))
	{
		if (check_type(line) == 1)
		{
			if (!(map_data->input.tx_south && map_data->input.tx_north
					&& map_data->input.tx_east && map_data->input.tx_east
					&& map_data->input.tx_west && map_data->input.tx_ceiling
					&& map_data->input.tx_floor))
			{
				ft_putstr_fd("Error\nMap before every argument\n", 2);
				free(line);
				destroy_mlx(map_data);
			}
			get_map(map_data, line, fd);
			return ;
		}
	}
	free(line);
	return ;
}
