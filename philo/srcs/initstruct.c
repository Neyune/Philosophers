

#include "philo.h"

int *check_arg(char **argv, int *args)
{
	int i;

	i = 0;
	while (argv[i + 1])
	{
		args[i] = ft_atoi(argv[i + 1]);
		if (args[i] == -1 || args[i] != ft_atol(argv[i + 1]))
			return (NULL);
		i++;
	}
	if (argv[5] == NULL)
		args[4] = -1;
	return (args);
}

t_data init_data(char **argv)
{
	t_data	data;

	if (check_arg(argv, (int*)&data) == NULL)
	{
		printf("Wrong args, you need to put 4 or 5 args (only unsigned int)\n");
		data.meat = 0;
	}
	data.dead = 0;
	data.EOeat = 0;
	// if (data.meat != 0)
	// {
		if (pthread_mutex_init(&data.m_sync, NULL))
		 	data.meat = 0;
		else if (pthread_mutex_init(&data.m_dead, NULL))
		{
			 pthread_mutex_destroy(&data.m_sync);
			 data.meat = 0;
		}
		else if (pthread_mutex_init(&data.m_EOeat, NULL))
		{
			pthread_mutex_destroy(&data.m_sync);
			pthread_mutex_destroy(&data.m_dead);
			data.meat = 0;
		}
	// }
	return (data);
}

t_philo *init_philo(t_data *data)
{
	int i;
	t_philo *philo;

	i = 0;
	philo = malloc(data->nbphilo * sizeof (*philo));
	while (i < data->nbphilo && philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].feat = 0;
		philo[i].seat = 0;
		if (pthread_mutex_init(&philo[i].mutex_fork, NULL))
		{
			free(philo);
			return (NULL);
		}
		if (i != data->nbphilo - 1)
			philo[i].mutex_fork2 = &philo[i + 1].mutex_fork;
		else
			philo[i].mutex_fork2 = &philo[0].mutex_fork;
		philo[i].data = data;
		i++;
	}
	data->stime = ft_time();
	return(philo);
}
