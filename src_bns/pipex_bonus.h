/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:31:46 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/28 14:54:15 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/src/libft.h"
# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_args	t_args;

struct s_args
{
	int		hd_status;
	int		command_number;
	char	**paths;
	char	**command;
	int		**pipes;
	int		*pids;
	int		in;
	int		out;
};

void	clean(t_args *args);
void	exec(t_args *args, int in, int out, char *command);
void	fail(t_args *args, char *msg1, char *msg2);
char	**get_first_command(char **av, int hd_status);
void	free_double_array(char **array);
int		**free_pipes(int **pipes, int i);
int		get_command_number(int ac, char **av);
char	**get_command(char *s, char **paths);
char	*get_command_path(char *s, char **paths);
int		*get_fds(int ac, char **av, int command_number);
char	*get_infile(char **av);
char	*get_path(char **envp);
int		heredoc(char *limiter);
int		heredoc_status(char **av);
void	init(t_args **args, int ac, char **av, char **envp);
void	pipeline(t_args *args, char **av);
void	print_double_array(char **array);
void	print_int_array(int *array, int size);

#endif
