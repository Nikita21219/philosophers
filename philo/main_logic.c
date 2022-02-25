/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:48:23 by bclarind          #+#    #+#             */
/*   Updated: 2022/02/25 17:50:24 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->die_write);
	if (philo->data->die != -1)
	{
		pthread_mutex_unlock(&philo->data->die_write);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->die_write);
	return (0);
}

void	write_die(t_philo *philo)
{
	pthread_mutex_unlock(philo->check_last_meal);
	pthread_mutex_lock(&philo->data->die_write);
	philo->data->die = philo->num + 1;
	printf("%lld %d died\n", get_timestamp() - \
	philo->data->start_timestamp, philo->data->die);
	pthread_mutex_unlock(&philo->data->die_write);
}

int	check_all_ate(t_philo *philosophers)
{
	t_philo	*philo;
	int		count;

	philo = philosophers;
	count = 0;
	while (philo)
	{
		pthread_mutex_lock(philo->ate_mutex);
		if (philo->ate)
			count++;
		pthread_mutex_unlock(philo->ate_mutex);
		philo = philo->next;
	}
	if (count == philosophers->data->num_of_philo)
	{
		pthread_mutex_lock(&philo->data->die_write);
		philo->data->die = philo->num + 1;
		pthread_mutex_unlock(&philo->data->die_write);
		return (1);
	}
	return (0);
}

void	print_who_died(t_philo *philosophers)
{
	t_philo	*philo;

	while (1)
	{
		philo = philosophers;
		if (philo->data->num_must_eat != -1 && check_all_ate(philosophers))
			break ;
		while (philo)
		{
			pthread_mutex_lock(philo->check_last_meal);
			if (get_timestamp() - philo->last_meal > philo->data->time_to_die)
			{
				write_die(philo);
				break ;
			}
			pthread_mutex_unlock(philo->check_last_meal);
			philo = philo->next;
			usleep(100);
		}
		if (is_die(philosophers))
			break ;
		usleep(100);
	}
}

void	main_logic(t_philo *philosophers)
{
	t_philo	*cur;

	cur = philosophers;
	philosophers->data->start_timestamp = get_timestamp();
	while (cur)
	{
		if (pthread_create(&cur->thread, NULL, thread, (void *)cur))
			break ;
		cur = cur->next;
	}
	print_who_died(philosophers);
	free_mutexes(philosophers);
	cur = philosophers;
	while (cur)
	{
		if (pthread_join(cur->thread, NULL))
			break ;
		cur = cur->next;
	}
}
