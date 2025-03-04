/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:50 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/04 09:59:40 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec(t_args *args, int in, int out, char *s_cmd)
{
	char	**command;
	char	cmd[32];

	command = get_command(s_cmd, args->paths);
	if (!command)
		error(PARSING_FAILED, TRY_AGAIN, args);
	if (dup2(in, STDIN_FILENO) == -1)
		error(REDIR, BAD_FD, args);
	if (dup2(out, STDOUT_FILENO) == -1)
		error(REDIR, BAD_FD, args);
	close_all(args);
	clean(args);
	execve(command[0], command, NULL);
	ft_strlcpy(cmd, ft_strtok(s_cmd, " "), 32);
	free_double_array(command);
	if (!args->paths)
		error(ENV_NOT_FND, cmd, args);
	error(CMD_NOT_FND, cmd, args);
}

void	setup_exec(t_args *args, int **pipes, int i)
{
	if (i == 0 && args->in)
	{
		if (args->in == -1)
			error(INFILE, DENIED_PERM, args);
		exec(args, args->in, pipes[0][1], args->commands[i]);
	}
	else if (i == args->command_number - 1)
	{
		if (args->out == -1)
			error(OUTFILE, DENIED_PERM, args);
		exec(args, pipes[i - 1][0], args->out, args->commands[i]);
	}
	else
	{
		exec(args, pipes[i - 1][0], pipes[i][1], args->commands[i]);
	}
}

void	pipeline(t_args *args)
{
	int	i;

	args->pids = malloc(sizeof(int) * args->command_number);
	args->pipes = get_pipes(args->command_number - 1);
	if (!args->pids || !args->pipes)
		return (clean(args));
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
	clean(args);
	return ;
}
