/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:48:23 by bclarind          #+#    #+#             */
/*   Updated: 2022/03/10 20:31:26 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_die(t_philo *philo)
{
	philo->data->die = philo->num + 1;
	printf("%lld %d died\n", get_timestamp() - \
	philo->data->start_timestamp, philo->data->die);
}

void	free_all_print_err(t_philo *philosophers, char *str)
{
	free_all(philosophers);
	print_error(str);
}

void	*print_died(void *args)
{
	t_philo	*philo;
	t_philo	*philosophers;

	philosophers = (t_philo *) args;
	while (1)
	{
		philo = philosophers;
		if (get_timestamp() - philo->last_meal > philo->data->time_to_die)
		{
			if (sem_wait(philo->data->sem_print))
				free_all_print_err(philosophers, "sem_wait() error");
			write_die(philo);
			if (sem_post(philo->data->sem))
				free_all_print_err(philosophers, "sem_post() error");
		}
		usleep(100);
	}
	return (NULL);
}

void	*check_ate(void *args)
{
	t_philo	*philosophers;
	int		i;

	i = 0;
	philosophers = (t_philo *) args;
	while (i++ < philosophers->data->num_of_philo)
	{
		if (sem_wait(philosophers->data->sem_all_ate))
		{
			free_all(philosophers);
			printf("sem_wait() error\n");
			break ;
		}
	}
	killall(philosophers);
	return (NULL);
}

void	main_logic(t_philo *philosophers)
{
	t_philo	*cur;

	cur = philosophers;
	philosophers->data->start_timestamp = get_timestamp();
	while (cur)
	{
		if (sem_wait(cur->data->sem))
			free_all_print_err(philosophers, "sem_wait() error");
		if (cur->data->num_must_eat != -1)
			if (sem_wait(cur->data->sem_all_ate))
				free_all_print_err(philosophers, "sem_wait() error");
		cur->pid = fork();
		if (cur->pid < 0)
			free_all_print_err(philosophers, "fork() error");
		else if (cur->pid == 0)
			process(cur);
		cur = cur->next;
	}
	if (philosophers->data->num_must_eat != -1)
		thread_eat_create(philosophers);
	if (sem_wait(philosophers->data->sem))
		free_all_print_err(philosophers, "sem_wait() error");
	killall(philosophers);
}
