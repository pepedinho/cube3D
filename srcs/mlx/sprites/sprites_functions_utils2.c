/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_functions_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 05:16:19 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 05:16:52 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

int	len_sprites(t_sprite *sprites)
{
	int	i;

	i = 0;
	while (sprites)
	{
		sprites = sprites->next;
		++i;
	}
	return (i);
}
