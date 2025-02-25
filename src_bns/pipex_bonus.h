/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:03:05 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/25 14:22:13 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/src/libft.h"
# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# define ERR_PROMPT "

typedef struct s_agrs	t_args;

struct s_args
{
	int		ac;
	char	**av;
	char	**paths;
	char	**command;
	int		*pipefd;
	int		*pipe_nb;
	pid_t	*pids;
	int		*pid_nb;
}

#endif
