/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:57:02 by madamou           #+#    #+#             */
/*   Updated: 2024/09/16 20:03:50 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
#define SPRITES_H

#include "../../../includes/cube3D.h"

void	random_enemies(t_map_data *data);
int len_sprites(t_sprite *sprites);
void	sort_sprites(int *order, double *dist, int amount);
void del_one_sprite(t_sprite **sprites, t_sprite *to_del);

#endif