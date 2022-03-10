/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:09:48 by bclarind          #+#    #+#             */
/*   Updated: 2022/03/04 12:38:41 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutexes(t_philo *philosophers)
{
	t_philo	*philo;

	philo = philosophers;
	while (philo)
	{
		if (pthread_mutex_destroy(philo->check_last_meal))
			return ;
		if (pthread_mutex_unlock(philo->mutex_l))
			return ;
		if (pthread_mutex_destroy(philo->mutex_l))
			return ;
		philo = philo->next;
	}
}

void	free_all(t_philo *philo, t_m *last_meal, t_m *ate_mut, t_m *forks)
{
	t_philo	*tmp;

	free(forks);
	free(ate_mut);
	free(last_meal);
	while (philo)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
}
