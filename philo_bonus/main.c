/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:29:15 by a1                #+#    #+#             */
/*   Updated: 2022/03/10 20:36:12 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep_eat(int time_to_eat)
{
	long long	i;

	i = get_timestamp();
	while (1)
	{
		if (get_timestamp() - i >= time_to_eat)
			return ;
		usleep(250);
	}
}

void	my_printf(char *str, t_philo *philo)
{
	if (philo->data->die == -1)
	{
		if (sem_wait(philo->data->sem_print))
			free_all_print_err(philo, "sem_wait() error");
		printf("%lld %d ", get_timestamp() - \
		philo->data->start_timestamp, philo->num + 1);
		printf("%s", str);
		if (sem_post(philo->data->sem_print))
			free_all_print_err(philo, "sem_post() error");
		return ;
	}
}

void	philo_eat(t_philo *philo)
{
	if (sem_wait(philo->data->sem_eat))
		free_all_print_err(philo, "sem_wait() error");
	my_printf("has taken a fork\n", philo);
	if (sem_wait(philo->data->sem_eat))
		free_all_print_err(philo, "sem_wait() error");
	my_printf("has taken a fork\n", philo);
	my_printf("is eating\n", philo);
	philo->last_meal = get_timestamp();
	my_usleep_eat(philo->data->time_to_eat);
	if (philo->data->num_must_eat != -1)
		philo->left_ate--;
	if (philo->left_ate <= 0)
		philo->ate++;
	if (philo->ate == 1)
		if (sem_post(philo->data->sem_all_ate))
			free_all_print_err(philo, "sem_post() error");
	if (sem_post(philo->data->sem_eat))
		free_all_print_err(philo, "sem_post() error");
	if (sem_post(philo->data->sem_eat))
		free_all_print_err(philo, "sem_post() error");
}

void	process(t_philo *philo)
{
	pthread_t	th_die;

	if (pthread_create(&th_die, NULL, print_died, (void *)philo))
		print_error("pthread_create() error");
	while (philo->data->die == -1)
	{
		philo_eat(philo);
		my_printf("is sleeping\n", philo);
		my_usleep(philo->data->time_to_sleep);
		my_printf("is thinking\n", philo);
	}
	if (pthread_join(th_die, NULL))
		print_error("pthread_join() error");
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (init_argv(&data, argc, argv))
		return (0);
	data.sem = sem_open("/forks", O_CREAT | O_EXCL, 0664, data.num_of_philo);
	if (data.sem == SEM_FAILED)
		print_error("SEM_FAILED");
	data.sem_eat = sem_open("/sem_eat", \
	O_CREAT | O_EXCL, 0664, data.num_of_philo);
	if (data.sem_eat == SEM_FAILED)
		print_error("SEM_FAILED");
	data.sem_all_ate = sem_open("/sem_all_ate", \
	O_CREAT | O_EXCL, 0664, data.num_of_philo);
	if (data.sem_all_ate == SEM_FAILED)
		print_error("SEM_FAILED");
	init_philosophers(&philo, &data);
	main_logic(philo);
	free_all(philo);
	return (0);
}
