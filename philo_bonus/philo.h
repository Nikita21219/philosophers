/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:36:29 by a1                #+#    #+#             */
/*   Updated: 2022/02/25 18:45:48 by bclarind         ###   ########.fr       */
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

typedef pthread_t		t_p;
typedef pthread_mutex_t	t_m;

typedef struct s_mutexes
{
	t_m	*forks;
	t_m	*ate_mutexes;
	t_m	print_mutex;
	t_m	*check_last_meal;
	t_m	*count_eat_mut;	
}	t_mutexes;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				die;
	long long		start_timestamp;
	t_m				print_mutex;
	t_m				die_write;
	t_mutexes		*mutexes;
}	t_data;

typedef struct s_philo
{
	int				num;
	int				left_ate;
	int				ate;
	long long		last_meal;
	t_p				thread;
	t_p				thread_die;
	t_m				*mutex_l;
	t_m				*mutex_r;
	t_m				*check_last_meal;
	t_m				*ate_mutex;
	t_data			*data;
	struct s_philo	*next;
}	t_philo;

int			init_argv(t_data *data, int argc, char **argv);
long long	ft_atoi_mod(const char *str);
int			ft_isdigit(int c);
long long	get_timestamp(void);
void		init_philosophers(t_philo **philo, t_data *data);
void		free_mutexes(t_philo *philosophers);
void		my_usleep(int time_to_sleep);
void		main_logic(t_philo *philosophers);
void		*thread(void *arg);
int			is_die(t_philo *philo);
void		init_mutexes(t_data *dt, t_m *mut, t_m *last_meal, t_m *ate_mut);
void		join_mut_and_ph(t_m *mut, t_philo *philo, t_m *l_m, t_m *ate_mut);
void		free_all(t_philo *philo, t_m *last_meal, t_m *ate_mut, t_m *forks);

#endif
