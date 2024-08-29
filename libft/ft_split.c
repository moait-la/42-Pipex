/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 02:04:58 by moait-la          #+#    #+#             */
/*   Updated: 2024/08/29 23:38:19 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words_num(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (count);
}

static void	ft_insert_word(char *res, char const *s, int len, int j)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		res[i] = s[j - len];
		i++;
		len--;
	}
	res[i] = '\0';
}

static char	**ft_insert(char **res, char const *s, char c, int words_num)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (i < words_num)
	{
		len = 0;
		while (s[j] == c && s[j] != '\0')
			j++;
		while (s[j] != c && s[j] != '\0')
		{
			j++;
			len++;
		}
		res[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!res[i])
			exit(1);
		ft_insert_word(res[i], s, len, j);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		words_num;
	int		i;
	char	**res;

	i = 0;
	if (!s)
		return (NULL);
	words_num = ft_words_num(s, c);
	res = (char **)malloc(sizeof(char *) * (words_num + 1));
	if (!res)
	{
		ft_putstr_fd("allocation failed\n", 2);
		exit(1);
	}
	res = ft_insert(res, s, c, words_num);
	if (res[0] == NULL)
	{
		ft_putstr_fd("Error: usage!\n", 2);
		exit(1);
	}
	return (res);
}
