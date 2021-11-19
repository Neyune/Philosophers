# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include <sys/time.h>

void *rout(void *nu)
{

	(void)nu;
	return (NULL);
}

int main()
{
 	pthread_t *philo;

	int i = 0;
	philo = malloc(200 * sizeof (*philo));
	while (i < 200)
	{
		pthread_create(&philo[i], NULL, rout, 0);
		i++;
	}
	return (0);
}
