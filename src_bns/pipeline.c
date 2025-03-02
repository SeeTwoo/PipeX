/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:50 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/02 23:26:18 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec(t_args *args, int in, int out, char *command)
{
	args->command = get_command(command, args->paths);
	if (!args->command)
		fail(args, "PipeX: parsing failed");
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close_all(args);
	execve(args->command[0], args->command, NULL);
	fail(args, "PipeX: command not found");
}

void	setup_exec(t_args *args, int i)
{
	if (i == 0 && args->in == -1)
		error("infile");
	else
		exec(args, args->in, args->pipes[0][1], args->commands[i]);
	if (i == args->command_number - 1 && args->out == -1)
		error("outfile");
	else
		exec(args, args->pipes[i - 1][0], args->out, args->commands[i]);
	exec(args, args->pipes[i - 1][0], args->pipes[i][1], args->commands[i]);
}

void	pipeline(t_args *args)
{
	int	i;
	int	*pids;
	int	**pipes;

	pids = malloc(sizeof(int) * args->command_number);
	pipes = get_pipes(args->command_number - 1);
	if (!pids || !pipes)
		return (free(pids), free(pipes));
	i = 0;
	while (i < args->command_number)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			setup_exec(args, i);
		i++;
	}
	close_all(args);
	while (--i >= 0)
		waitpid(pids[i], NULL, 0);
	return ;
}
