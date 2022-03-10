#include "philo_bonus/philo.h"

sem_t	*s;
int	counter = 0;

void	*w1(void *args)
{
	(void) args;
	int	loc;
	int i = 0;
	while (i++ < 100000)
	{
		sem_wait(s);
		loc = counter;
		loc++;
		counter = loc;
		sem_post(s);
	}
	return (NULL);
}

void	*w2(void *args)
{
	(void) args;
	// sem_post(dt->sem);
	int	loc;
	int i = 0;
	while (i++ < 100000)
	{
		sem_wait(s);
		loc = counter;
		loc--;
		counter = loc;
		sem_post(s);
	}
	return (NULL);
}

int main()
{
	// t_data		data;
	// pthread_t	t1;
	// pthread_t	t2;
	pid_t		pid;

	pid = fork();
	sem_unlink("/sem");
	s = sem_open("/sem", O_CREAT | O_EXCL, 0644, 1);
	if (s == SEM_FAILED)
		printf("SEM_FAILED\n");
	w1(NULL);
	w2(NULL);
	sem_unlink("/sem");
	printf("%d\n", counter);
	return (0);
}

// int main()
// {
// 	t_data		data;
// 	pthread_t	t1;
// 	pthread_t	t2;

// 	sem_unlink("/test");
// 	data.sem = sem_open("/test", O_CREAT | O_EXCL, 0644, 1);
// 	pthread_create(&t1, NULL, w1, &data);
// 	pthread_create(&t2, NULL, w2, &data);
// 	pthread_join(t1, NULL);
// 	pthread_join(t2, NULL);
// 	sem_unlink("/test");
// 	return (0);
// }
