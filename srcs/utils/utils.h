/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:55:20 by madamou           #+#    #+#             */
/*   Updated: 2024/09/15 02:38:13 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

double	rand_value(double min, double max);
int	get_map_height(char **map);
void	swap(int *a, int *b);
void	swap_double(double *a, double *b);

#endif