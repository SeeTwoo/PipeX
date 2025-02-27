/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:50 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/27 19:00:14 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**first_command(char **av, int hd_status)
{
	if (hd_status == 1)
		return (&av[3]);
	return (&av[2]);
}

void	exec(t_args *args, int in, int out, char *command)
{
	args->command = get_command(command, args->paths);
	dup2(in, STDIN_FILENO);
	close(in);
	dup2(out, STDOUT_FILENO);
	close(out);
	execve(args->command[0], args->command, NULL);
	fail(args, "command not found: ", args->command[0]);
}

void	pipeline(t_args *args, char **av)
{
	int		i;
	int		*pids;

	i = 0;
	pids = malloc(sizeof(int) * args->command_number);
	av = first_command(av, args->hd_status);
	while (i < args->command_number)
	{
		pids[i] = fork();
		if (i == 0)
		if (pids[i] == 0)
			exec(args, &(args->fds[i * 2]), av_commands[i]);
		i++;
	}
	i--;
	while (i >= 0)
		waitpid(pids[i++], NULL, 0);
}
