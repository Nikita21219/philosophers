/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:06:46 by bclarind          #+#    #+#             */
/*   Updated: 2022/03/10 21:00:28 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philosopher(t_p thread, int num, t_data *data, t_p thread_die)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)malloc(sizeof(t_philo));
	if (!philosopher)
		return (NULL);
	philosopher->next = NULL;
	philosopher->thread = thread;
	philosopher->thread_die = thread_die;
	philosopher->num = num;
	philosopher->data = data;
	philosopher->last_meal = get_timestamp();
	philosopher->ate = -1;
	philosopher->left_ate = -1;
	if (philosopher->data->num_must_eat != -1)
	{
		philosopher->ate = 0;
		philosopher->left_ate = philosopher->data->num_must_eat;
	}
	return (philosopher);
}

t_philo	*ft_last_el(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_el_add_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	if (!new)
		return (1);
	if (lst && *lst)
	{
		last = ft_last_el(*lst);
		if (!last)
			return (1);
		last->next = new;
	}
	else if (lst)
		*lst = new;
	return (0);
}

int	init_philosophers(t_philo **philo, t_data *data)
{
	int	i;
	t_p	th;
	t_p	th_die;

	i = 0;
	th = NULL;
	th_die = NULL;
	while (i < data->num_of_philo)
	{
		if (ft_el_add_back(philo, init_philosopher(th, i++, data, th_die)))
		{
			while (i--)
			{
				free(*philo);
				*philo = (*philo)->next;
			}
			free(philo);
			return (1);
		}
	}
	return (0);
}

int	init_mutexes(t_data *dt, t_m *mut, t_m *last_meal, t_m *ate_mut)
{
	int	i;

	i = 0;
	while (i < dt->num_of_philo)
	{
		if (pthread_mutex_init(&last_meal[i], NULL))
			return (1);
		if (pthread_mutex_init(&mut[i], NULL))
			return (1);
		if (pthread_mutex_init(&ate_mut[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
