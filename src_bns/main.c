/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:38:10 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/27 12:32:11 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path(char **envp)
{
	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (!(*envp))
		return (NULL);
	return (&((*envp)[5]));
}

int	get_command_number(int ac, char **av)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		return (ac - 4);
	else
		return (ac - 3);
}

char	*get_infile(char **av)
{
	return (av[1]);
}

char	*get_outfile(char **av)
{
	return (av[4]);
}

int	*get_fds(char **av, int command_number)
{
	int		*fds;
	int		i;

	fds = malloc(sizeof(int) * (command_number * 2));
	if (!fds)
		return (NULL);
	i = 0;
	while (i < command_number * 2)
		fds[i++] = -1;
	fds[0] = open(get_infile(av), O_RDONLY);
	i = 0;
	while (i < command_number)
	{
		pipe(&fds[i * 2]);
		i++;
	}
	fds[(i * 2) - 1] = open(get_outfile(av), O_WRONLY | O_TRUNC | O_CREAT);
	return (fds);
}

void	free_double_array(char **array)
{
	int	i;
	
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	print_double_array(char **array)
{
	while (*array)
	{
		ft_printf("%s\n", *array);
		array++;
	}
	ft_printf("\n");
}

void	print_int_array(int *array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%d\n", array[i]);
		i++;
	}
	ft_printf("\n");
}

void	clean(t_args *args)
{
	if (!args)
		return ;
	if (args->paths)
		free_double_array(args->paths);
	if (args->command)
		free_double_array(args->command);
	if (args->fds)
		free(args->fds);
	free(args);
}

void	fail(t_args *args, char *msg1, char *msg2)
{
	clean(args);
	//perror(REDBG);
	perror("PipeX:");
	//perror(RESET);
	perror(msg1);
	perror(msg2);
	exit(EXIT_FAILURE);
}

void	init(t_args **args, int ac, char **av, char **envp)
{
	*args = malloc(sizeof(t_args));
	if (!args)
		fail(*args, "malloc trouble: ", "try again and hope for the best\n");
	(*args)->command_number = get_command_number(ac, av);
	(*args)->paths = ft_split(get_path(envp), ":");
	(*args)->command = NULL;
	(*args)->fds = get_fds(av, (*args)->command_number);
	if (!(*args)->paths || !(*args)->fds)
		fail(*args, "init failed: ", "try again and hope for the best\n");
}

int	main(int ac, char **av, char **envp)
{
	t_args	*args;

	if (ac != 5)
		return (0);
	args = NULL;
	init(&args, ac, av, envp);
	ft_printf("%spaths are :%s\n\n", BYELLOW, RESET);
	print_double_array(args->paths);
	ft_printf("%sfds are :%s\n\n", BYELLOW, RESET);
	print_int_array(args->fds, 4);
	clean(args);
	return (0);
}
