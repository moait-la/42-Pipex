/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 06:18:29 by moait-la          #+#    #+#             */
/*   Updated: 2024/07/22 01:58:58 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/pipex.h"
#include "./get_next_line/get_next_line.h"

void	last_command(int ac, char **av, char **envp, int childp_nbr)
{
	int		i;
	int		outfile_fd;
	pid_t	pid;
	char	*path;
	char	**cmd_args;

	pid = fork();
	if (pid < 0)
		exit(1);
	i = -1;
	if (pid == 0)
	{
		outfile_fd = open_file(av[ac - 1], 3);
		cmd_args = ft_split(av[ac - 2], ' ');
		path = get_path(cmd_args[0], envp);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		if (execve(path, cmd_args, NULL) == -1)
			exit(6);
	}
	else
	{
		while (++i < childp_nbr + 1)
			wait(NULL);
	}
}

void	child_process(char **cmd_args, char *path)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		exit(3);
	pid = fork();
	if (pid < 0)
		exit (4);
	else if (pid == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		execve(path, cmd_args, NULL);
	}
	else
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
}

static void	multiple_cmds(int ac, char **av, char **envp)
{
	int		i;
	int		childp_nbr;
	int		infile_fd;
	char	**cmd_args;
	char	*path;

	infile_fd = open_file(av[1], 1);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	childp_nbr = 0;
	i = 2;
	while (i < ac - 2)
	{
		cmd_args = ft_split(av[i], ' ');
		path = get_path(cmd_args[0], envp);
		child_process(cmd_args, path);
		free(path);
		ft_free(cmd_args);
		i++;
		childp_nbr++;
	}
	last_command(ac, av, envp, childp_nbr);
}

int	main(int ac, char **av, char **envp)
{
	if (ac < 5)
	{
		ft_putstr_fd("Error: usage!\n", 2);
		exit(1);
	}
	else if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		here_doc(ac, av, envp);
	else
		multiple_cmds(ac, av, envp);
	return (0);
}
