/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:38:10 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/26 13:36:54 by wbeschon         ###   ########.fr       */
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
	char	*infile;
	char	*outfile;

	fds = malloc(sizeof(int) * (command_number * 2));
	if (!fds)
		return (NULL);
	infile = get_infile(av);
	outfile = get_outfile(av);
	fds[0] = open(infile, O_RDONLY);
	i = 0;
	while (i < command_number)
		pipe(&fds[1 + i++ * 2]);
	fds[i * 2 + 1] = open(outfile, O_WRONLY | O_TRUNC | O_CREAT);
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

void	print_int_array(int *array)
{
	while (*array)
	{
		ft_printf("%d\n", *array);
		array++;
	}
	ft_printf("\n");
}

void	clean(t_args *args)
{
	if (args->paths)
		free_double_array(args->paths);
	if (args->command)
		free_double_array(args->command);
	if (args->fds)
		free(args->fds);
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

void	init(t_args *args, int ac, char **av, char **envp)
{
	args = malloc(sizeof(t_args));
	if (!args)
		fail(args, "malloc trouble: ", "try again and hope for the best ");
	args->command_number = get_command_number(ac, av);
	args->paths = ft_split(get_path(envp), ":");
	args->command = NULL;
	args->fds = get_fds(av, args->command_number);
	if (!args->fds)
	{
		ft_printf("failing\n\n");
		fail(args, "malloc trouble: ", "try again and hope for the best ");
	}
}

int	main(int ac, char **av, char **envp)
{
	t_args	*args;

	if (ac != 5)
		return (0);
	args = NULL;
	init(args, ac, av, envp);
	ft_printf("%scommand number is:%s %d\n\n", YELLOW, RESET, args->command_number);
	ft_printf("%spaths are :%s\n\n", YELLOW, RESET);
	print_double_array(args->paths);
	ft_printf("%sfds are :%s\n\n", YELLOW, RESET);
	print_int_array(args->fds);
	clean(args);
	return (0);
}
