/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:05:54 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/20 14:03:03 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		pipefd[2];
	pid_t	pid[2];
	t_args	*args;

	args = parsing(ac, av, envp);
	if (!args)
		fail(args, "\e[41mPipeX:\e[0m args parsing failed\n", NULL);
	if (pipe(pipefd) == -1)
		fail(args, "\e[41mPipeX:\e[0m pipe creation failed\n", pipefd);
	pid[0] = fork();
	if (pid[0] == -1)
		fail(args, "\e[41mPipeX:\e[0m fork failed\n", pipefd);
	if (pid[0] == 0)
		input(args, pipefd);
	pid[1] = fork();
	if (pid[1] == -1)
		fail(args, "\e[41mPipeX:\e[0m fork failed\n", pipefd);
	if (pid[1] == 0)
		output(args, pipefd);
	close_tab(pipefd, 2);
	wait_tab(pid, 2);
	free_args(args);
	return (0);
}
