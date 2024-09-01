/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:11:50 by madamou           #+#    #+#             */
/*   Updated: 2024/09/01 20:53:47 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *ptr, int len_realloc)
{
	char	*tmp;
	int		i;

	i = ft_strlen(ptr);
	tmp = malloc(sizeof(char) * (i + len_realloc + 1));
	if (!tmp)
	{
		free(ptr);
		return (NULL);
	}
	tmp[0] = '\0';
	tmp = ft_strcpy(tmp, ptr);
	free(ptr);
	return (tmp);
}
