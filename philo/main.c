/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:29:15 by a1                #+#    #+#             */
/*   Updated: 2022/02/25 18:29:27 by bclarind         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->die_write);
	if (philo->data->die == -1)
	{
		pthread_mutex_unlock(&philo->data->die_write);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%lld %d ", get_timestamp() - \
		philo->data->start_timestamp, philo->num + 1);
		printf("%s", str);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->die_write);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_l);
	my_printf("has taken a fork\n", philo);
	pthread_mutex_lock(philo->mutex_r);
	my_printf("has taken a fork\n", philo);
	my_printf("is eating\n", philo);
	pthread_mutex_lock(philo->check_last_meal);
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(philo->check_last_meal);
	my_usleep_eat(philo->data->time_to_eat);
	if (philo->data->num_must_eat != -1)
		philo->left_ate--;
	pthread_mutex_lock(philo->ate_mutex);
	if (philo->left_ate <= 0)
		philo->ate = 1;
	pthread_mutex_unlock(philo->ate_mutex);
	pthread_mutex_unlock(philo->mutex_l);
	pthread_mutex_unlock(philo->mutex_r);
}

void	*thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->num % 2 == 0)
		usleep(10000);
	pthread_mutex_lock(&philo->data->die_write);
	while (philo->data->die == -1)
	{
		pthread_mutex_unlock(&philo->data->die_write);
		philo_eat(philo);
		if (is_die(philo))
			return (NULL);
		my_printf("is sleeping\n", philo);
		my_usleep(philo->data->time_to_sleep);
		if (is_die(philo))
			return (NULL);
		my_printf("is thinking\n", philo);
		pthread_mutex_lock(&philo->data->die_write);
	}
	pthread_mutex_unlock(&philo->data->die_write);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	t_m		*forks;
	t_m		*ate_mutexes;
	t_m		*check_last_meal;

	philo = NULL;
	if (init_argv(&data, argc, argv))
		return (0);
	forks = malloc(sizeof(t_m) * data.num_of_philo);
	ate_mutexes = malloc(sizeof(t_m) * data.num_of_philo);
	check_last_meal = malloc(sizeof(t_m) * data.num_of_philo);
	init_mutexes(&data, forks, check_last_meal, ate_mutexes);
	init_philosophers(&philo, &data);
	join_mut_and_ph(forks, philo, check_last_meal, ate_mutexes);
	main_logic(philo);
	free_all(philo, check_last_meal, ate_mutexes, forks);
	return (0);
}
