/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:54:04 by bclarind          #+#    #+#             */
/*   Updated: 2022/03/10 20:29:31 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	killall(t_philo *philo)
{
	while (philo)
	{
		if (kill(philo->pid, SIGKILL))
			exit(1);
		philo = philo->next;
	}
	exit(0);
}

void	thread_eat_create(t_philo *philo)
{
	pthread_t	th;

	if (pthread_create(&th, NULL, check_ate, (void *)philo))
	{
		free_all(philo);
		print_error("sem_wait() error");
	}
	pthread_detach(th);
}

void	sem_unlinks(void)
{
	sem_unlink("/forks");
	sem_unlink("/sem_eat");
	sem_unlink("/sem_print");
	sem_unlink("/die_write");
	sem_unlink("/sem_all_ate");
}
