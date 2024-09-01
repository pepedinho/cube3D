/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str_char2d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:34:54 by madamou           #+#    #+#             */
/*   Updated: 2024/09/01 18:35:43 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*add_string_char_2d(char ***tab, char *str)
{
	char	**new;
	int		i;
	char	**buff;

	buff = *tab;
	new = malloc(sizeof(char *) * (ft_strlen_2d(buff) + 1 + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (buff && buff[i])
	{
		new[i] = buff[i];
		if (!new[i])
			return (NULL);
		i++;
	}
	new[i] = str;
	if (!new[i])
		return (NULL);
	new[++i] = NULL;
	free(buff);
	*tab = new;
	return (tab);
}
