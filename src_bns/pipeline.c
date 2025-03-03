/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:50 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/03 12:50:48 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec(t_args *args, int in, int out, char *s_cmd)
{
	char	**command;

	command = get_command(s_cmd, args->paths);
	if (!command)
		error("PipeX: parsing failed");
	if (dup2(in, STDIN_FILENO) == -1)
		error("PipeX: redirection");
	if (dup2(out, STDOUT_FILENO) == -1)
		error("PipeX: redirection");
	close_all(args);
	execve(command[0], command, NULL);
	error("PipeX: command not found");
}

void	setup_exec(t_args *args, int **pipes, int i)
{
	if (i == 0 && args->in)
		exec(args, args->in, pipes[0][1], args->commands[i]);
	else if (i == args->command_number - 1)
		exec(args, pipes[i - 1][0], args->out, args->commands[i]);
	else
		exec(args, pipes[i - 1][0], pipes[i][1], args->commands[i]);
}

void	pipeline(t_args *args)
{
	int	i;

	args->pids = malloc(sizeof(int) * args->command_number);
	args->pipes = get_pipes(args->command_number - 1);
	if (!args->pids || !args->pipes)
	{
		free(args->pids);
		free_pipes(args->pipes, args->command_number - 1);
		return ;
	}
	i = 0;
	while (i < args->command_number)
	{
		args->pids[i] = fork();
		if (args->pids[i] == 0)
			setup_exec(args, args->pipes, i);
		i++;
	}
	close_all(args);
	while (--i >= 0)
		waitpid(args->pids[i], NULL, 0);
	free(args->pids);
	free_pipes(args->pipes, args->command_number - 1);
	return ;
}
