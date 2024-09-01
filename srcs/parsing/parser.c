/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:12:58 by itahri            #+#    #+#             */
/*   Updated: 2024/09/01 14:12:54 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	return (0);
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
	if (type == 0)
		return (0);
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			while (line[i] && ft_isspace(line[i]))
				i++;
			break ;
		}
		i++;
	}
	path = ft_substr(line, i, ft_strlen(line));
	if (!path)
		return (0);
	return (assign_path(path, map_data, type), 1);
}

int	parse_line(char *line, int fd, t_map_data *map_data)
{
	(void)fd;
	if (!get_path(line, map_data, check_type(line)))
	{
		printf("nothing on this line\n");
		return (0);
	}
	return (1);
}

t_map_data	*get_map_data(char *filename)
{
	int			fd;
	char		*line;
	t_map_data	*map_data;

	map_data = malloc(sizeof(t_map_data));
	if (!map_data)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, fd, map_data);
		free(line);
		line = get_next_line(fd);
	}
	return (map_data);
}
