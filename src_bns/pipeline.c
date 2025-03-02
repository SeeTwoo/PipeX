/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:50 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/02 15:46:26 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_first_command(char **av, int hd_status)
{
	if (hd_status == 1)
		return (&av[3]);
	return (&av[2]);
}

void	exec(t_args *args, int in, int out, char *command)
{
	args->command = get_command(command, args->paths);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close_all(args);
	execve(args->command[0], args->command, NULL);
	fail(args, "PipeX: command not found");
}

void	setup_exec(t_args *args, int i, char **av)
{
	if (i == 0)
	{
		if (args->hd_status == 0)
			args->in = open(av[-1], O_RDONLY);
		if (args->in == -1)
			fail(args, "Pipex: file error");
		exec(args, args->in, args->pipes[0][1], av[i]);
	}
	else if (i == args->command_number - 1)
	{
		if (args->hd_status == 1)
			args->out = open(av[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			args->out = open(av[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (args->out == -1)
			fail(args, "PipeX: file error");
		exec(args, args->pipes[i - 1][0], args->out, av[i]);
	}
	exec(args, args->pipes[i - 1][0], args->pipes[i][1], av[i]);
}

void	pipeline(t_args *args, char **commands)
{
	int		i;

	i = 0;
	while (i < args->command_number)
	{
		args->pids[i] = fork();
		if (args->pids[i] == 0)
			setup_exec(args, i, commands);
		i++;
	}
	close_all(args);
	while (--i >= 0)
		waitpid(args->pids[i], NULL, 0);
	return ;
}
