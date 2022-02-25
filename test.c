
#include "philo/philo.h"

void	*thread1(void *arg)
{
	int	*i;

	i = (int *) arg;
	while (*i < 100)
		(*i)++;
	return (NULL);
}

int	main()
{
	pthread_t	t1;
	// pthread_t	t2;
	int			*i;

	i = NULL;
	*i = 0;
	pthread_create(&t1, NULL, thread1, i);
	// pthread_create(&t2, NULL, thread2, i);
	return (0);
}
