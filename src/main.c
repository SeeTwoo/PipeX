/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:40:21 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/04 11:26:44 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(t_args *args, int in, int out, char *s_cmd)
{
	char	**command;
	char	cmd[32];

	if (!s_cmd[0])
		error(CMD_NOT_FND, "you did not type any command", args);
	command = get_command(s_cmd, args->paths);
	if (!command)
		error(PARSING_FAILED, TRY_AGAIN, args);
	if (dup2(in, STDIN_FILENO) == -1)
		error(REDIR, BAD_FD, args);
	if (dup2(out, STDOUT_FILENO) == -1)
		error(REDIR, BAD_FD, args);
	close_all(args);
	execve(command[0], command, NULL);
	ft_strlcpy(cmd, ft_strtok(s_cmd, " "), 32);
	free_double_array(command);
	if (!args->paths)
		error(ENV_NOT_FND, cmd, args);
	error(CMD_NOT_FND, cmd, args);
}

void	setup_exec(t_args *args, int *pipefd, int i)
{
	if (i == 0)
	{
		if (args->in == -1)
			error(INFILE, DENIED_PERM, args);
		exec(args, args->in, pipefd[1], args->commands[0]);
	}
	else
	{
		if (args->out == -1)
			error(OUTFILE, DENIED_PERM, args);
		exec(args, pipefd[0], args->out, args->commands[1]);
	}
}

void	pipeline(t_args *args)
{
	int	i;

	if (pipe(args->pipefd) == -1)
		error(PIPE_FAILED, TRY_AGAIN, args);
	i = 0;
	while (i < 2)
	{
		args->pids[i] = fork();
		if (args->pids[i] == 0)
			setup_exec(args, args->pipefd, i);
		i++;
	}
	close_all(args);
	while (--i >= 0)
		waitpid(args->pids[i], NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_args	args;

	if (ac != 5)
	{
		ft_printf("Usage: ./pipex_bonus <infile> <\"cmd1\"> <\"cmd2\"> ");
		ft_printf("<outfile>\n");
		exit(EXIT_FAILURE);
	}
	init(&args, ac, av, envp);
	pipeline(&args);
	return (0);
}
