
#include "includes/philo.h"

void *rout(void *)
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
		pthread_create(&philo[i], NULL, (t_routine)rout, 0);
		i++;
	}
	return (0);
}
