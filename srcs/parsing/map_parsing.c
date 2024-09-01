/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:23:54 by itahri            #+#    #+#             */
/*   Updated: 2024/09/01 16:24:50 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

int	is_valide_box(char c)
{
	if (c == 'N')
		return (1);
	else if (c == 'W')
		return (1);
	else if (c == 'E')
		return (1);
	else if (c == 'S')
		return (1);
	else if (c == '0')
		return (1);
	else if (c == '1')
		return (1);
	return (0);
}

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

int	y_size_map(char *line, int fd)
{
	char	*n_line;
	int		i;

	n_line = line;
	i = 0;
	while (n_line)
	{
		free(n_line);
		n_line = get_next_line(fd);
		if (check_map_line(n_line))
			i++;
	}
	return (i);
}

void	reajust_read_head(int *fd, char *filename, int i)
{
	int		j;
	char	*line;

	close(*fd);
	j = 0;
	*fd = open(filename, O_RDONLY);
	line = get_next_line(*fd);
	while (j < i && line)
	{
		free(line);
		line = get_next_line(*fd);
		j++;
	}
	free(line);
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
