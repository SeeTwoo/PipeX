/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:03:05 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/25 17:28:59 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/src/libft.h"
# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# define ERR_PROMPT "PipeX:"

typedef struct s_args	t_args;

struct s_args
{
	int		ac;
	char	**av;
	char	**paths;
	char	**command;
	int		*pipefd;
	int		pipe_nb;
	pid_t	*pids;
	int		pid_nb;
};

void	clean(t_args *args);
int		*close_pipes(int *pipefd, int pipe_nb);
int		*create_pids(t_args *args);
int		*create_pipes(t_args *args);
void	exec(t_args *args);
void	fail(t_args *args);
void	free_double_array(char **tab);
void	get_command(t_args *args, int i);
int		init(t_args *args, int ac, char **av, char **envp);
void	parsing(int ac, char **av, char **envp, t_args *args);

#endif
