/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:04:52 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 04:12:04 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_2d(char **split)
{
	int	index;

	if (!split)
		return;
	index = 0;
	while (split[index])
	{
		free(split[index]);
		index++;
	}
	free(split);
}
