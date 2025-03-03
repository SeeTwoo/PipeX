/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:50 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/03 12:27:05 by walter           ###   ########.fr       */
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
	close(in);
	close(out);
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
			setup_exec(args, pipes, i);
		i++;
	}
	close_all(args, pipes);
	while (--i >= 0)
		waitpid(pids[i], NULL, 0);
	return ;
}
