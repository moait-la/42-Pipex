/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:17:54 by moait-la          #+#    #+#             */
/*   Updated: 2024/03/25 00:24:28 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/pipex.h"
#include "./libft/libft.h"

void	ft_free(char **ptr)
{
	char	**temp;

	if (ptr == NULL)
		return ;
	temp = ptr;
	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
	free(temp);
}

char	*ft_getenv(char **envp)
{
	char	*path_word;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		path_word = ft_substr(envp[i], 0, 4);
		if (!ft_strncmp(path_word, "PATH", 5))
			break ;
		free(path_word);
		i++;
	}
	free(path_word);
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	return (path);
}

char	*get_path(char *cmd, char **envp)
{
	char	*path;
	char	**all_paths;
	char	*cmd_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	else
	{
		path = ft_getenv(envp);
		all_paths = ft_split(path, ':');
		i = -1;
		free(path);
		while (all_paths[++i] != NULL)
		{
			path = ft_strjoin(all_paths[i], "/");
			cmd_path = ft_strjoin(path, cmd);
			free(path);
			if (access(cmd_path, X_OK) == 0)
				return (ft_free(all_paths), cmd_path);
			if (all_paths[i + 1] != NULL)
				free(cmd_path);
		}
	}
	return (perror("Command not found"), cmd_path);
}

int	open_file(char *name, int nbr)
{
	int	fd;

	fd = 0;
	if (nbr == 1)
		fd = open(name, O_RDONLY, 0666);
	else if (nbr == 2)
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else if (nbr == 3)
		fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1 && nbr == 1)
	{
		ft_putstr_fd("Error: opening infile\n", 2);
		exit(1);
	}
	else if (fd == -1 && (nbr == 2 || nbr == 3))
	{
		ft_putstr_fd("Error: opening outfile\n", 2);
		exit(1);
	}
	return (fd);
}

int	my_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if ((*s1 - *s2) != 0)
			return (1);
		s1++;
		s2++;
	}
	if (*s1 == '\n' && *s2 == '\0')
		return (0);
	return (*s1 - *s2);
}
