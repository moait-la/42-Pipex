/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:04:47 by moait-la          #+#    #+#             */
/*   Updated: 2024/03/17 00:37:58 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free_(char **block)
{
	if (*block)
	{
		free(*block);
		*block = NULL;
	}
	return (NULL);
}

char	*ft_reset_keep(char *keep)
{
	char	*new_keep;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (keep[i] && keep[i] != '\n')
		i++;
	if (keep[i] == '\0' || keep[i + 1] == '\0')
		return (ft_free_(&keep));
	while (keep[(i + 1) + j])
		j++;
	new_keep = (char *)malloc(j + 1);
	if (!new_keep)
		return (NULL);
	k = 0;
	while (k < j)
	{
		new_keep[k] = keep[(i + 1) + k];
		k++;
	}
	new_keep[j] = '\0';
	ft_free_(&keep);
	return (new_keep);
}

char	*ft_get_line(char	*keep)
{
	char	*line;
	char	*new_keep;
	int		i;

	i = 0;
	while (keep[i] && keep[i] != '\n')
		i++;
	if (keep[i] == '\0')
	{
		new_keep = ft_strdup(keep);
		if (!new_keep)
			return (NULL);
		return (new_keep);
	}
	line = (char *)malloc(i + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (keep[++i] != '\n')
		line[i] = keep[i];
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

void	*ft_read_fd(int fd, ssize_t read_b, char **keep, char **valid_address)
{
	char	*buffer;

	*valid_address = (char *)malloc(1);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer || !*valid_address)
		return (NULL);
	while (1)
	{
		read_b = read(fd, buffer, BUFFER_SIZE);
		if (read_b <= 0)
			break ;
		buffer[read_b] = '\0';
		*keep = ft_strjoin(*keep, buffer);
		if (!*keep)
			return (NULL);
		if (check_for_n(buffer) == 1)
			break ;
	}
	ft_free_(&buffer);
	if (read_b == -1)
		return (NULL);
	if (read_b == 0 && !*keep)
		return (NULL);
	return (*valid_address);
}

char	*get_next_line(int fd)
{
	char		*check;
	char		*line;
	char		*valid_address;
	static char	*keep;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	check = ft_read_fd(fd, 1, &keep, &valid_address);
	if (!check)
	{
		ft_free_(&keep);
		return (ft_free_(&valid_address));
	}
	free((void *)valid_address);
	line = ft_get_line(keep);
	keep = ft_reset_keep(keep);
	return (line);
}
