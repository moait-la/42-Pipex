/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:45:45 by moait-la          #+#    #+#             */
/*   Updated: 2024/03/19 01:30:03 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_combine_str(char const *s1, char const *s2, char *res)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		res[i] = s2[k];
		k++;
		i++;
	}
	res[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;

	res = NULL;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
	{
		ft_putstr_fd("allocation failed\n", 2);
		exit(1);
	}
	ft_combine_str(s1, s2, res);
	return (res);
}
