/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:05:13 by bclarind          #+#    #+#             */
/*   Updated: 2022/03/10 20:52:49 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

long long int	ft_atoi_mod(const char *str)
{
	int				sign;
	long long int	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || \
	*str == '\f' || *str == '\r' || *str == '\x0B')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit((int) *str))
		res = res * 10 + (int) *str++ - '0';
	return (res * sign);
}

long long	get_timestamp(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

void	join_mut_and_ph(t_m *mut, t_philo *philo, t_m *l_m, t_m *ate_mut)
{
	int	i;

	i = 0;
	while (philo->next)
	{
		philo->mutex_l = &mut[i];
		philo->mutex_r = &mut[i + 1];
		philo->check_last_meal = &l_m[i];
		philo->ate_mutex = &ate_mut[i];
		philo = philo->next;
		i++;
	}
	philo->mutex_l = &mut[i];
	philo->mutex_r = &mut[0];
	philo->check_last_meal = &l_m[i];
	philo->ate_mutex = &ate_mut[i];
}

void	my_usleep(int time_to_sleep)
{
	long long	i;

	i = get_timestamp();
	while (1)
	{
		if (get_timestamp() - i >= time_to_sleep)
			return ;
		usleep(250);
	}
}
