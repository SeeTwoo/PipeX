/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:11:38 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/04 11:18:50 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
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

void	close_all(t_args *args);
void	error(char *msg1, char *msg2, t_args *args);
void	free_double_array(char **array);
char	**get_command(char *s, char *paths);
void	init(t_args *args, int ac, char **av, char **envp);

#endif
