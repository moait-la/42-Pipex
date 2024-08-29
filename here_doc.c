/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:37:16 by moait-la          #+#    #+#             */
/*   Updated: 2024/03/26 07:52:36 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/pipex.h"

static void	read_from_stdin(char **av)
{
	int		fds[2];
	char	*line;
	char	*display_msj;

	display_msj = "heredoc> ";
	if (pipe(fds) == -1)
		exit(5);
	while (1)
	{
		write(0, display_msj, ft_strlen(display_msj));
		line = get_next_line(0);
		if (!line || !my_strcmp(line, av[2]))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fds[1]);
		free(line);
	}
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
}

void	here_doc(int ac, char **av, char **envp)
{
	char	**cmd_args;
	char	*path;
	int		childp_nbr;
	int		i;

	read_from_stdin(av);
	childp_nbr = 0;
	i = 3;
	while (i < ac - 2)
	{
		cmd_args = ft_split(av[i], ' ');
		path = get_path(cmd_args[0], envp);
		child_process(cmd_args, path);
		if (ft_strncmp(path, cmd_args[0], ft_strlen(path)) != 0)
			free(path);
		ft_free(cmd_args);
		i++;
		childp_nbr++;
	}
	last_command(ac, av, envp, childp_nbr);
}
