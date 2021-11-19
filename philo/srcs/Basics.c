/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:48:52 by ereali            #+#    #+#             */
/*   Updated: 2021/11/18 18:01:54 by ereali           ###   ########.fr       */
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

long long	ft_time(void)
{
	t_timeval		now;
	unsigned long	time;

	if (gettimeofday(&now, NULL) != 0)
	{
		write(1, "ERROR\n", 6);
		return (-1);
	}
	time = ((now.tv_sec * 1000) + (now.tv_usec / 1000));
	return (time);
}

void	ft_msleep(t_philo **philo, long long msec)
{
	long long	timestamp;

	timestamp = ft_time();
	while (!check_death(philo) && !check_eoeat(philo)
		&& ft_time() - timestamp < msec)
		usleep(1000);
}

void	ft_clear(t_philo **philo, int j, int k, int l)
{
	int	i;

	i = 0;
	if (j == -1)
		j = (*philo)->data->nbphilo;
	philojoin(philo, l);
	i = 0;
	while (i < k)
	{
		pthread_mutex_destroy(&(*philo)[i].m_feat);
		i++;
	}
	i = 0;
	while (i < j)
	{
		pthread_mutex_destroy(&(*philo)[i].mutex_fork);
		i++;
	}
	free(*philo);
}

// pthread_mutex_destroy(&(*philo)->data->m_coor);
// pthread_mutex_destroy(&(*philo)->data->m_dead);
// pthread_mutex_destroy(&(*philo)->data->m_eoeat);
// pthread_mutex_destroy(&(*philo)->data->m_printf);
