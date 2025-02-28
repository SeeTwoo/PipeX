/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:12:50 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/28 15:29:12 by wbeschon         ###   ########.fr       */
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
	close(in);
	dup2(out, STDOUT_FILENO);
	close(out);
	execve(args->command[0], args->command, NULL);
	fail(args, "command not found: ", args->command[0]);
}

void	setup_exec(t_args *args, int i, char **av)
{
	if (i == 0)
		exec(args, args->in, args->pipes[0][1], av[i]);
	else if (i == args->command_number - 1)
		exec(args, args->pipes[i - 1][0], args->out, av[i]);
	else
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
	while (--i >= 0)
		waitpid(args->pids[i], NULL, 0);
	ft_printf("done waiting \n");
	return ;
}
