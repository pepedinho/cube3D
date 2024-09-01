/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:06:54 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 13:38:25 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		cpt++;
	}
	if (i - 1 < 0)
		return (0);
	if (s[i - 1] == c)
		cpt--;
	return (cpt);
}

static char	*ft_norminette(char const *s, int i, int j)
{
	int		k;
	char	*str;

	k = 0;
	str = malloc(sizeof(char) * (j + 1));
	if (str == NULL)
		return (NULL);
	while (k < j)
	{
		str[k] = s[i - j + k];
		k++;
	}
	str[k] = '\0';
	return (str);
}

static int	ft_free_split(char **split, int index)
{
	if (split[index] == NULL)
	{
		while (index >= 0)
			free(split[index--]);
		free(split);
		return (0);
	}
	return (1);
}

static int	ft_split_words(char **split, char const *s, char c)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	index = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		while (s[i] && s[i] != c)
		{
			i++;
			j++;
		}
		if (s[i - 1] != c)
		{
			split[index] = ft_norminette(s, i, j);
			if (ft_free_split(split, index++) == 0)
				return (0);
		}
	}
	split[index] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (split == NULL)
		return (NULL);
	if (ft_count_word(s, c) == 0)
	{
		split[0] = NULL;
		return (split);
	}
	if (ft_split_words(split, s, c) == 0)
		return (NULL);
	return (split);
}

/*int	main(void)
{
 	char **tab;
 	// char * invalidReadCheck = 0;
 	tab = ft_split("hello!", ' ');
 	printf("%s\n", tab[0]);
 	printf("%s\n", tab[1]);
}*/
