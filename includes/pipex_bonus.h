/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:31:46 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/03 21:07:01 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h" 
# include <errno.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_args	t_args;

struct s_args
{
	int		command_number;
	int		in;
	int		out;
	int		ac;
	char	**commands;
	char	*paths;
	int		**pipes;
	int		*pids;
};

void	clean(t_args *args);
void	close_all(t_args *args);
void	error(char *msg1, char *msg2, t_args *args);
void	exec(t_args *args, int in, int out, char *command);
void	free_double_array(char **array);
int		**free_pipes(int **pipes, int i);
int		get_command_number(int ac, char **av);
char	**get_command(char *s, char *paths);
char	*get_command_path(char *s, char *paths);
int		*get_fds(int ac, char **av, int command_number);
char	*get_infile(char **av);
char	*get_path(char **envp);
int		**get_pipes(int size);
int		heredoc(char *limiter);
void	heredoc_init(t_args *args, int ac, char **av, char **envp);
void	init(t_args *args, int ac, char **av, char **envp);
void	pipeline(t_args *args);
void	print_double_array(char **array);
void	print_int_array(int *array, int size);

#endif
