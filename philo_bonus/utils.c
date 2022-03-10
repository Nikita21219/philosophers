/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:05:13 by bclarind          #+#    #+#             */
/*   Updated: 2022/03/10 19:13:09 by bclarind         ###   ########.fr       */
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

	if (gettimeofday(&timestamp, NULL) == -1)
		print_error("gettimeofday error");
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
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

void	free_all(t_philo *philo)
{
	t_philo	*tmp;

	while (philo)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
	sem_unlink("/forks");
	sem_unlink("/sem_eat");
	sem_unlink("/sem_print");
	sem_unlink("/die_write");
	sem_unlink("/sem_all_ate");
}
