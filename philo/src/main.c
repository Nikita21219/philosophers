/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:29:15 by a1                #+#    #+#             */
/*   Updated: 2022/02/21 21:03:38 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

long long	get_timestamp(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

void	my_usleep(int time_to_sleep, t_philo *philo)
{
	long long i;

	i = get_timestamp();
	while (philo->data->die == -1 && !philo->data->all_ate)
	{
		if (get_timestamp() - i >= time_to_sleep)
			break ;
		usleep(50);
	}
}

void	my_usleep_eat(int time_to_eat, t_philo *philo)
{
	long long i;

	i = get_timestamp();
	pthread_mutex_lock(philo->check_last_meal);
	while (philo->data->die == -1 && !philo->data->all_ate)
	{
		if (get_timestamp() - i >= time_to_eat)
			break ;
		usleep(50);
	}
	pthread_mutex_unlock(philo->check_last_meal);
}

void	my_printf(char *str, t_philo *philo)
{
	if (philo->data->die == -1 && !philo->data->all_ate)
	{
		pthread_mutex_lock(philo->data->print_mutex);
		printf("%lld %d ", get_timestamp() - philo->data->start_timestamp, philo->num + 1);
		printf("%s", str);
		pthread_mutex_unlock(philo->data->print_mutex);
	}
}

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

t_philo	*init_philosopher(int l_fork, int r_fork, pthread_t thread, int num, t_data *data, pthread_t thread_die)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)malloc(sizeof(t_philo));
	if (!philosopher)
		return (NULL);
	philosopher->next = NULL;
	philosopher->l_fork = l_fork;
	philosopher->r_fork = r_fork;
	philosopher->thread = thread;
	philosopher->thread_die = thread_die;
	philosopher->num = num;
	philosopher->data = data;
	philosopher->last_meal = get_timestamp();
	if (philosopher->data->num_must_eat != -1)
		philosopher->count_eat = 0;
	else
		philosopher->count_eat = -1;
	return (philosopher);
}

t_philo	*ft_last_el(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_el_add_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	if (!new)
		return ;
	if (lst && *lst)
	{
		last = ft_last_el(*lst);
		last->next = new;
	}
	else if (lst)
		*lst = new;
}

void	init_philosophers(t_philo **philosophers, int number_of_philo, t_data *data)
{
	int				i;
	pthread_t		thread;
	pthread_t		thread_die;

	i = 0;
	thread = NULL;
	thread_die = NULL;
	while (i < number_of_philo)
	{
		ft_el_add_back(philosophers, init_philosopher(i, i + 1, thread, i, data, thread_die));
		i++;
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_l);
	my_printf("has taken a fork\n", philo);
	pthread_mutex_lock(philo->mutex_r);
	my_printf("has taken a fork\n", philo);
	my_printf("is eating\n", philo);
	philo->last_meal = get_timestamp();
	my_usleep_eat(philo->data->time_to_eat, philo);
	philo->count_eat++;
	pthread_mutex_unlock(philo->mutex_l);
	pthread_mutex_unlock(philo->mutex_r);
}

void	join_mutexes_with_philo(pthread_mutex_t *mutexes, t_philo *philo, pthread_mutex_t *check_last_meal)
{
	int	i;
	t_philo *start_philo;

	i = 0;
	start_philo = philo;
	while (philo->next)
	{
		philo->mutex_l = &mutexes[i];
		philo->mutex_r = &mutexes[i + 1];
		philo = philo->next;
		i++;
	}
	philo->mutex_l = &mutexes[i];
	philo->mutex_r = &mutexes[0];

	i = 0;
	while (start_philo)
	{
		start_philo->check_last_meal = &check_last_meal[i];
		start_philo = start_philo->next;
		i++;
	}
}

void	init_mutexes(pthread_mutex_t *mutexes, int num_of_philo)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
		pthread_mutex_init(&mutexes[i++], NULL);
}

int	is_not_num(char **argv)
{
	int	i;
	int	j;

	i = -1;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
		}
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (*s++)
		counter++;
	return (counter);
}

int	over_int(char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (ft_strlen(argv[i]) > 10)
			return (1);
		if (ft_atoi_mod(argv[i]) > INT_MAX || ft_atoi_mod(argv[i]) < INT_MIN)
			return (1);
		i++;
	}
	return (0);
}

int	is_error(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || ft_atoi_mod(*(argv + 1)) < 1)
		return (1);
	if (is_not_num(argv + 1) || over_int(argv + 1, argc))
		return (1);
	return (0);
}

int	init_argv(t_data *data, int argc, char **argv, pthread_mutex_t *print_mutex)
{
	if (is_error(argc, argv))
	{
		printf("Error\n");
		return (1);
	}
	data->num_of_philo = ft_atoi_mod(*(argv + 1));
	data->time_to_die = ft_atoi_mod(*(argv + 2));
	data->time_to_eat = ft_atoi_mod(*(argv + 3));
	data->time_to_sleep = ft_atoi_mod(*(argv + 4));
	data->die = -1;
	data->print_mutex = print_mutex;
	data->all_ate = 0;
	if (argc == 6)
		data->num_must_eat = ft_atoi_mod(*(argv + 5));
	else
		data->num_must_eat = -1;
	return (0);
}

void	*thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->num % 2 == 0)
		usleep(10000);
	while (philo->data->die == -1 && !philo->data->all_ate)
	{
		philo_eat(philo);
		my_printf("is sleeping\n", philo);
		my_usleep(philo->data->time_to_sleep, philo);
		my_printf("is thinking\n", philo);
	}
	return (NULL);
}

void	check_all_ate(t_philo *philo)
{
	t_philo	*cur;
	int		count;

	while (!philo->data->all_ate)
	{
		cur = philo;
		count = 0;
		while (cur)
		{
			if (cur->count_eat == cur->data->num_must_eat)
				count++;
			if (count == cur->data->num_of_philo)
			{
				cur->data->all_ate = 1;
				break ;
			}
			cur = cur->next;
			usleep(100);
		}
	}
}

void	free_mutexes(t_philo *philosophers)
{
	t_philo	*philo;

	philo = philosophers;
	while (philo)
	{
		if (pthread_mutex_unlock(philo->mutex_l))
			return ;
		if (pthread_mutex_destroy(philo->mutex_l))
			return ;
		philo = philo->next;
	}
}

void	*thread_die(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (philo->data->die == -1 && !philo->data->all_ate)
	{
		pthread_mutex_lock(philo->check_last_meal);
		if (get_timestamp() - philo->last_meal > philo->data->time_to_die)
		{
			pthread_mutex_unlock(philo->check_last_meal);
			pthread_mutex_lock(philo->data->print_mutex);
			philo->data->die = philo->num + 1;
			printf("%lld %d died\n", get_timestamp() - philo->data->start_timestamp, philo->data->die);
			return (NULL);
		}
		pthread_mutex_unlock(philo->check_last_meal);
		usleep(500);
	}
	return (NULL);
}

void	print_who_died(t_philo *philosophers)
{
	t_philo	*cur;
	int		i;

	i = 0;
	cur = philosophers;
	while (i < philosophers->data->num_of_philo)
	{
		if (pthread_create(&cur->thread_die, NULL, thread_die, (void *)cur))
			break ;
		i++;
		cur = cur->next;
	}
	if (philosophers->data->num_must_eat != -1)
		check_all_ate(philosophers);
	while (philosophers->data->die == -1 && !philosophers->data->all_ate)
		usleep(100);
	free_mutexes(philosophers);
	i = 0;
	cur = philosophers;
	while (i++ < philosophers->data->num_of_philo)
	{
		if (pthread_detach(cur->thread_die))
			break ;
		cur = cur->next;
	}
}

int	main(int argc, char **argv)
{
	int				i;
	t_philo			*philosophers;
	t_data			data;
	pthread_mutex_t	*mutexes;
	t_philo			*cur;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*check_last_meal;

	pthread_mutex_init(&print_mutex, NULL);
	if (init_argv(&data, argc, argv, &print_mutex))
		return (0);
	mutexes = malloc(sizeof(pthread_mutex_t) * data.num_of_philo);
	check_last_meal = malloc(sizeof(pthread_mutex_t) * data.num_of_philo);
	init_mutexes(mutexes, data.num_of_philo);
	init_mutexes(check_last_meal, data.num_of_philo);
	init_philosophers(&philosophers, data.num_of_philo, &data);
	join_mutexes_with_philo(mutexes, philosophers, check_last_meal);
	i = 0;
	cur = philosophers;
	data.start_timestamp = get_timestamp();
	while (i < data.num_of_philo)
	{
		if (pthread_create(&cur->thread, NULL, thread, (void *)cur))
			break ;
		i++;
		cur = cur->next;
	}
	i = 0;
	cur = philosophers;
	print_who_died(philosophers);
	while (i++ < data.num_of_philo)
	{
		if (pthread_join(cur->thread, NULL))
			break ;
		cur = cur->next;
	}
	return (0);
}
