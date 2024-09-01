/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:18:28 by madamou           #+#    #+#             */
/*   Updated: 2024/09/01 21:19:29 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

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
		i++;
	}
	tmp[i] = NULL;
	*map_cpy = tmp;
}

int	flood_fill(t_map_data *data)
{
	char	**map_cpy;

	crate_map_copy(data, &map_cpy);
	if (!map_cpy)
		return (0);
	print_2d_array(map_cpy);
	ft_free_2d(map_cpy);
	return (1);
}
