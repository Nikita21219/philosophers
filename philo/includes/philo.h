/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:36:29 by a1                #+#    #+#             */
/*   Updated: 2022/02/21 20:53:25 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				all_ate;
	int				die;
	long long		start_timestamp;
	pthread_mutex_t	*print_mutex;
}	t_data;

typedef struct s_philo
{
	int				num;
	int				l_fork;
	int				r_fork;
	int				count_eat;
	pthread_mutex_t	*mutex_l;
	pthread_mutex_t	*mutex_r;
	pthread_mutex_t	*check_last_meal;
	long long		last_meal;
	pthread_t		thread;
	pthread_t		thread_die;
	t_data			*data;
	struct s_philo	*next;
}	t_philo;

#endif
