/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_playable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:18:28 by madamou           #+#    #+#             */
/*   Updated: 2024/09/01 22:46:13 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void change_if_find_player(char **line)
{
	char *check;
	char *buff;

	buff = *line;
	check = ft_strchr(buff, 'N');
	if (check)
		check[0] = '0';
	check = ft_strchr(buff, 'S');
	if (check)
		check[0] = '0';
	check = ft_strchr(buff, 'E');
	if (check)
		check[0] = '0';
	check = ft_strchr(buff, 'W');
	if (check)
		check[0] = '0';
}		
					
void	crate_map_copy(t_map_data *data, char ***map_cpy)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (ft_strlen_2d(data->map + 1)));
	if (!tmp)
		return ;
	while (data->map[i])
	{
		tmp[i] = ft_strdup(data->map[i]);
		if (!tmp[i])
			ft_free_2d(tmp);
		change_if_find_player(&tmp[i]);
		i++;
	}
	tmp[i] = NULL;
	*map_cpy = tmp;
}

int	check_next_cases(char **map_cpy, int y, int x)
{
	int	cpt;

	cpt = 0;
	if (y == 0 || x == 0)
		return (0);
	if (x == ft_strlen(map_cpy[y]) || y == ft_strlen_2d(map_cpy))
		return (0);
	if (map_cpy[y + 1][x] == ' ' || map_cpy[y + 1][x] == '\0')
		return (0);
	if (map_cpy[y - 1][x] == ' ' || map_cpy[y - 1][x] == '\0')
		return (0);
	if (map_cpy[y][x + 1] == ' ' || map_cpy[y][x + 1] == '\0')
		return (0);
	if (map_cpy[y][x - 1] == ' ' || map_cpy[y][x + 1] == '\0')
		return (0);
	return (1);
}

int	blob_the_map(char **map_cpy)
{
	int	x;
	int	y;

	y = 0;
	while (map_cpy[y])
	{
		x = 0;
		while (map_cpy[y][x])
		{
			if (map_cpy[y][x] == '0')
			{
				if (!check_next_cases(map_cpy, y, x))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map_playable(t_map_data *data)
{
	char	**map_cpy;

	crate_map_copy(data, &map_cpy);
	if (!map_cpy)
		return (0);
	if (blob_the_map(map_cpy) == 0)
		return (0);
	print_2d_array(map_cpy);
	ft_free_2d(map_cpy);
	return (1);
}
