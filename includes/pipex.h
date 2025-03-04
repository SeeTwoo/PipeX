/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:11:38 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/04 10:48:31 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/src/libft.h"
# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_args	t_args;

struct s_args
{
	int		in;
	int		out;
	int		ac;
	char	**commands;
	char	*paths;
	int		pipefd[2];
	int		pids[2];
};

void	close_tab(int *tab, size_t size);
void	fail(t_args *args, char *msg, int pipefd[2], int fd);
t_args	*free_args(t_args *args);
char	**free_double_array(char **tab);
char	**get_command(char *s, char **paths);
void	input(t_args *args, int pipefd[2]);
void	output(t_args *args, int pipefd[2]);
t_args	*parsing(int ac, char **av, char **envp);
void	wait_tab(pid_t *tab, size_t size);

#endif
