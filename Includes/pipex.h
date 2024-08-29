/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moait-la <moait-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:42:46 by moait-la          #+#    #+#             */
/*   Updated: 2024/03/25 01:34:19 by moait-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

void	child_process(char **cmd_args, char *path);
void	last_command(int ac, char **av, char **envp, int childp_nbr);
void	here_doc(int ac, char **av, char **envp);
void	ft_free(char **ptr);
char	*get_path(char *cmd, char **envp);
char	*ft_getenv(char **envp);
int		open_file(char *name, int nbr);
int		my_strcmp(char *s1, char *s2);

#endif