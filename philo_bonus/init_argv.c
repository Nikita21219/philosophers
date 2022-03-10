/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:03:28 by bclarind          #+#    #+#             */
/*   Updated: 2022/03/10 20:25:20 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_not_num(char **argv)
{
	int	i;
	int	j;

	i = -1;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (1);
	}
	return (0);
}

int	ft_strlen(const char *s)
{
	int	counter;

	counter = 0;
	while (*s++)
		counter++;
	return (counter);
}

int	over_int(char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (ft_strlen(argv[i]) > 10)
			return (1);
		if (ft_atoi_mod(argv[i]) > INT_MAX || ft_atoi_mod(argv[i]) < INT_MIN)
			return (1);
		i++;
	}
	return (0);
}

int	is_error(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || ft_atoi_mod(*(argv + 1)) < 1)
		return (1);
	if (is_not_num(argv + 1) || over_int(argv + 1, argc))
		return (1);
	return (0);
}

int	init_argv(t_data *data, int argc, char **argv)
{
	if (is_error(argc, argv))
		print_error("Error");
	data->num_of_philo = ft_atoi_mod(*(argv + 1));
	data->time_to_die = ft_atoi_mod(*(argv + 2));
	data->time_to_eat = ft_atoi_mod(*(argv + 3));
	data->time_to_sleep = ft_atoi_mod(*(argv + 4));
	data->sem_print = sem_open("/sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (data->sem_print == SEM_FAILED)
		print_error("SEM_FAILED");
	data->die_write = sem_open("/die_write", O_CREAT | O_EXCL, 0644, 1);
	if (data->die_write == SEM_FAILED)
		print_error("SEM_FAILED");
	data->die = -1;
	data->num_must_eat = -1;
	if (argc == 6)
	{
		data->num_must_eat = ft_atoi_mod(*(argv + 5));
		if (data->num_must_eat == 0)
			exit(0);
	}
	sem_unlinks();
	return (0);
}
