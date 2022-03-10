/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:02:16 by bclarind          #+#    #+#             */
/*   Updated: 2022/03/10 21:03:40 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_mut(t_m **forks, t_m **ate_m, t_m **last_meal, t_data data)
{
	*forks = malloc(sizeof(t_m) * data.num_of_philo);
	if (!(*forks))
		return (1);
	*ate_m = malloc(sizeof(t_m) * data.num_of_philo);
	if (!(*ate_m))
	{
		free((*forks));
		return (1);
	}
	*last_meal = malloc(sizeof(t_m) * data.num_of_philo);
	if (!last_meal)
	{
		free((*forks));
		free((*ate_m));
		return (1);
	}
	return (0);
}
