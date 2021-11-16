/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:32:46 by ereali            #+#    #+#             */
/*   Updated: 2021/11/16 07:33:11 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setdeath(t_data *data, t_philo **philo)
{
	int i;

	while (data->dead == 0 && data->EOeat != data->nbphilo && data->meat != 0)
	{
		i = 0;
		while (i < data->nbphilo && data->dead == 0 && data->EOeat != data->nbphilo)
		{
			if ((ft_time() - (*philo)[i].data->stime) - (*philo)[i].feat >= data->die)
			{
				if (pthread_mutex_lock(&data->m_dead))
					return (-1);
				data->dead = 1;
				pthread_mutex_unlock(&data->m_dead);
				printf("%lld %d died\n", (ft_time() - data->stime), i + 1);
			}
			i++;
		}
		usleep(1000);
	}
	return (0);
}

typedef void *(*t_routine)(void *);


int	philocreate(t_philo **philo)
{
	int i;

	i = 0;
	(*philo)->data->stime = ft_time();
	(*philo)->data->dead = 0;
	while (i < (*philo)->data->nbphilo)
	{
		if (pthread_create(&(*philo)[i].philosophe, NULL, (t_routine)Routine, &(*philo)[i]))
		{
			ft_clear(philo, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void    *Routine(t_philo *philo)
{
	// tableau int pour avoir que f[2] test 2 90000 200 200 1
	int i;
	int f1;
	int f2;

	f1 = 0;
	f2 = 0;
	i = 0;
	pthread_mutex_lock(&philo->data->m_sync);
	pthread_mutex_unlock(&philo->data->m_sync);
	if (philo->philo_id % 2 == 1)
	{
		ft_msleep(&philo->data, 1);
	}
	while (philo->data->dead == 0 && philo->data->meat != 0 && philo->data->EOeat != philo->data->nbphilo)
	{
		if (philo->data->dead == 0 && philo->data->EOeat != philo->data->nbphilo)
			printf("%lld %d is thinking\n", (ft_time() - philo->data->stime), philo->philo_id);
		if (philo->data->dead == 0 && philo->data->EOeat != philo->data->nbphilo)
		{
			f1 = 1;
			pthread_mutex_lock(philo->mutex_fork2);
			if (philo->data->nbphilo != 1)
				{
					f2 = 1;
					pthread_mutex_lock(&philo->mutex_fork);
				}
			if (philo->data->dead == 0 && philo->data->EOeat != philo->data->nbphilo)
				printf("%lld %d has taken a fork\n", (ft_time() - philo->data->stime), philo->philo_id);
			// return (0); // fct prtege et destroy mutex
		}
		if (f1 && f2)
		{
			philo->feat = (ft_time() - philo->data->stime);
		}
		if (philo->data->dead == 0 && f1 && f2 && philo->data->EOeat != philo->data->nbphilo)
		{
			printf("%lld %d has taken a fork\n", (ft_time() - philo->data->stime), philo->philo_id);
			printf("%lld %d is eating\n", (ft_time() - philo->data->stime), philo->philo_id);
			ft_msleep(&philo->data, philo->data->eat);
		}  // return (0); // fct prtege et destroy mutex
		if (f1)
			pthread_mutex_unlock(philo->mutex_fork2);
		if (f2)
			pthread_mutex_unlock(&philo->mutex_fork);
		if (philo->data->meat > 0 && (i + 1) == philo->data->meat && f1 && f2)
		{
			pthread_mutex_lock(&philo->data->m_EOeat);
			philo->data->EOeat += 1;
			pthread_mutex_unlock(&philo->data->m_EOeat);
		}
		if (philo->data->dead == 0 && (f1 && f2) && philo->data->EOeat != philo->data->nbphilo)
		{
			printf("%lld %d is sleeping\n", (ft_time() - philo->data->stime), philo->philo_id);
			ft_msleep(&philo->data, philo->data->sleep);
		}
		i++;
		while (philo->data->dead == 0
			&& (philo->data->nbphilo == 1 && i >= 1))
			usleep(150);
	}
	return (philo);
}

int philojoin(t_philo **philo)
{
	int i;

	i = 0;
	while (i < (*philo)->data->nbphilo
		&& pthread_join((*philo)[i].philosophe, NULL) == 0)
		i++;
	if (i == (*philo)->data->nbphilo)
	 	return (0);
	return (-1);
}

int main(int argc, char **argv)
{
	t_data  data;
	t_philo *philo;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong args, you need to put 4 or 5 args (only unsigned int)\n");
		return (1);
	}
	data = init_data(argv);
	if (data.meat == 0 || data.nbphilo == 0)
		return (1);
	philo = init_philo(&data);
	if (philo == NULL)
		return (1);
	if (pthread_mutex_lock(&data.m_sync) || philocreate(&philo))
		return(2);
	pthread_mutex_unlock(&data.m_sync);
	if (setdeath(&data, &philo) || philojoin(&philo))
	{
		ft_clear(&philo, -1);
		return(3);
	}
	ft_clear(&philo, -1);
	return (0);
}
