/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstruct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 04:29:30 by ereali            #+#    #+#             */
/*   Updated: 2021/11/18 06:50:39 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*check_arg(char **argv, int *args)
{
	int	i;

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

t_data	init_data(char **argv)
{
	t_data	data;

	if (check_arg(argv, (int *)&data) == NULL)
	{
		printf("Wrong args, you need to put 4 or 5 args (only unsigned int)\n");
		data.meat = 0;
	}
	if (pthread_mutex_init(&data.m_sync, NULL))
		data.meat = 0;
	return (data);
}

int init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->m_dead, NULL))
	{
		pthread_mutex_destroy(&data->m_sync);
		return (1);
	}
	else if (pthread_mutex_init(&data->m_eoeat, NULL))
	{
		pthread_mutex_destroy(&data->m_sync);
		pthread_mutex_destroy(&data->m_dead);
		return (1);
	}
	else if (pthread_mutex_init(&data->m_printf, NULL))
	{
		pthread_mutex_destroy(&data->m_sync);
		pthread_mutex_destroy(&data->m_dead);
		pthread_mutex_destroy(&data->m_eoeat);
		return (1);
	}
	return (0);
}
t_philo	*init_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	data->eoeat = 0;
	philo = malloc(data->nbphilo * sizeof (*philo));
	while (i < data->nbphilo && philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].feat = 0;
		philo[i].seat = 0;
		if (pthread_mutex_init(&philo[i].mutex_fork, NULL))
		{
			ft_clear(&philo, i, 0);
			return (NULL);
		}
		if (i != data->nbphilo - 1)
			philo[i].mutex_fork2 = &philo[i + 1].mutex_fork;
		else
			philo[i].mutex_fork2 = &philo[0].mutex_fork;
		philo[i].data = data;
		i++;
	}
	return (philo);
}
