/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 06:18:32 by moait-la          #+#    #+#             */
/*   Updated: 2024/08/28 02:24:12 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/pipex.h"

void	second_child_process(char **av, char **envp, int *fds)
{
	int		outfile_fd;
	char	*path;
	char	**cmd_args;

	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	outfile_fd = open_file(av[4], 2);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	cmd_args = ft_split(av[3], ' ');
	path = get_path(cmd_args[0], envp);
	if (execve(path, cmd_args, NULL) == -1)
		exit(6);
}

void	first_child_process(char **av, char **envp, int *fds)
{
	int		infile_fd;
	char	*path;
	char	**cmd_args;

	infile_fd = open_file(av[1], 1);
	dup2(infile_fd, STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close(infile_fd);
	close(fds[1]);
	cmd_args = ft_split(av[2], ' ');
	path = get_path(cmd_args[0], envp);
	if (execve(path, cmd_args, NULL) == -1)
		exit(5);
}

int	main(int ac, char **av, char **envp)
{
	int		fds[2];
	pid_t	pid_1;
	pid_t	pid_2;

	if (ac != 5)
		return (ft_putstr_fd("./pipex infile cmd cmd outfile\n", 1), 1);
	if (pipe(fds) == -1)
		exit(2);
	pid_1 = fork();
	if (pid_1 < 0)
		exit(3);
	else if (pid_1 == 0)
		first_child_process(av, envp, fds);
	pid_2 = fork();
	if (pid_2 < 0)
		exit(4);
	else if (pid_2 == 0)
		second_child_process(av, envp, fds);
	close(fds[1]);
	close(fds[0]);
	wait(NULL);
	wait(NULL);
	return (0);
}
