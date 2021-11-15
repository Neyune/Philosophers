/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:48:52 by ereali            #+#    #+#             */
/*   Updated: 2021/10/19 00:26:11 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	if (str[i] == '\0' || str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb);
}

long int	ft_atol(char *str)
{
	long int		i;
	long int		nb;

	i = 0;
	nb = 0;
	if (str[i] == '\0' || str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb);
}

long long ft_time(void)
{
	t_timeval now;
	unsigned long time;

	if (gettimeofday(&now, NULL) != 0)
	{
		write(1, "ERROR\n", 6);
		return (-1);
	}
	time = ((now.tv_sec * 1000) + (now.tv_usec / 1000));
	return (time);
}

void ft_msleep(t_data **data,long long msec)
{

	long long timestamp;

	timestamp = ft_time();
	while ((*data)->dead == 0 && (*data)->EOeat != (*data)->nbphilo
		&& ft_time() - timestamp < msec)
		usleep(150);
}

void ft_clear(t_philo **philo)
{
	pthread_mutex_destroy(&(*philo)->data->m_sync);
	pthread_mutex_destroy(&(*philo)->data->m_EOeat);
	pthread_mutex_destroy(&(*philo)->data->m_dead);
	// while i ...
	// pthread_mutex_destroy(&(*philo)[i].mutex_fork);
	free(*philo);
}
