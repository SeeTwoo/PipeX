/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:51:40 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/20 12:31:03 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fail(t_args *args, char *msg, int pipefd[2])
{
	close_tab(pipefd, 2);
	free_args(args);
	if (msg)
		perror(msg);
	exit(EXIT_FAILURE);
}

void	input(t_args *args, int pipefd[2])
{
	int		in_fd;

	in_fd = open(args->av[1], O_RDONLY);
	if (in_fd == -1)
		fail(args, "PipeX: infile opening failed\n", pipefd);
	args->command = get_command(args->av[2], args->paths);
	if (!args->command)
		fail(args, "PipeX: input command parsing failed\n", pipefd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		fail(args, "PipeX: pipe redirection failed\n", pipefd);
	if (dup2(in_fd, STDIN_FILENO) == -1)
		fail(args, "PipeX: infile redirection failed\n", pipefd);
	close(in_fd);
	close_tab(pipefd, 2);
	execve(args->command[0], args->command, NULL);
	fail(args, NULL, pipefd);
}

void	output(t_args *args, int pipefd[2])
{
	int		out_fd;

	out_fd = open(args->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
		fail(args, "PipeX: output file opening failed\n", pipefd);
	args->command = get_command(args->av[3], args->paths);
	if (!args->command)
		fail(args, "PipeX: output command parsing failed\n", pipefd);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		fail(args, "PipeX: outfile redirection failed\n", pipefd);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		fail(args, "PipeX: pipe  redirection failed\n", pipefd);
	close(out_fd);
	close_tab(pipefd, 2);
	execve(args->command[0], args->command, NULL);
	fail(args, NULL, pipefd);
}
