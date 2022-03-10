/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:36:29 by a1                #+#    #+#             */
/*   Updated: 2022/03/10 20:33:28 by bclarind         ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>

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
	sem_t			*sem_eat;
	sem_t			*sem_all_ate;
	sem_t			*sem;
	sem_t			*sem_print;
	sem_t			*die_write;
}	t_data;

typedef struct s_philo
{
	int				num;
	int				left_ate;
	int				ate;
	long long		last_meal;
	t_p				thread;
	t_p				thread_die;
	pid_t			pid;
	t_data			*data;
	struct s_philo	*next;
}	t_philo;

int			init_argv(t_data *data, int argc, char **argv);
long long	ft_atoi_mod(const char *str);
int			ft_isdigit(int c);
long long	get_timestamp(void);
void		init_philosophers(t_philo **philo, t_data *data);
void		my_usleep(int time_to_sleep);
void		main_logic(t_philo *philosophers);
void		process(t_philo *philo);
void		free_all(t_philo *philo);
void		*print_died(void *args);
void		print_error(char *str);
void		killall(t_philo *philo);
void		thread_eat_create(t_philo *philo);
void		*check_ate(void *args);
void		sem_unlinks(void);
void		free_all_print_err(t_philo *philosophers, char *str);

#endif
