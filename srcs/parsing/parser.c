/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:12:58 by itahri            #+#    #+#             */
/*   Updated: 2024/09/01 18:59:36 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// TODO check if no space between type and path
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
		map_data->tx_north = path;
	else if (type == SO)
		map_data->tx_south = path;
	else if (type == WE)
		map_data->tx_west = path;
	else if (type == EA)
		map_data->tx_east = path;
	else if (type == F)
		map_data->tx_floor = path;
	else if (type == C)
		map_data->tx_ceiling = path;
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
	i += 2;
	while (line[i] && ft_isspace(line[i]))
		i++;
	path = ft_substr(line, i, ft_strlen(line + i) - 1);
	if (!path)
		return (0);
	return (assign_path(path, map_data, type), 1);
}

int	parse_line(char *line, int fd, t_map_data *map_data)
{
	if (!get_path(line, map_data, check_type(line)))
	{
		if (check_type(line) == 1)
			get_map(map_data, line, fd);
		return (0);
	}
	return (1);
}

t_map_data	*get_map_data(char *filename)
{
	int			fd;
	char		*line;
	int			i;
	t_map_data	*map_data;

	i = 0;
	map_data = malloc(sizeof(t_map_data));
	if (!map_data)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map_data->map_path = filename;
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, fd, map_data);
		line = get_next_line(fd);
	}
	return (map_data);
}
