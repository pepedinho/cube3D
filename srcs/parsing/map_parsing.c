/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:23:54 by itahri            #+#    #+#             */
/*   Updated: 2024/09/01 18:50:24 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

int	check_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\n')
		return (0);
	return (1);
}

char	*correct_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
	return (line);
}

int	get_map(t_map_data *map_data, char *line, int fd)
{
	char	**map;

	map = NULL;
	while (line)
	{
		if (check_map_line(line))
		{
			if (!add_string_char_2d(&map, correct_line(line)))
				return (0);
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	map_data->map = map;
	return (1);
}
