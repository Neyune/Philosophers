/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:32:46 by ereali            #+#    #+#             */
/*   Updated: 2021/11/18 06:49:23 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setdeath(t_data *data, t_philo **philo)
{
	int	i;

	while (!check_death(philo) && !check_eoeat(philo) && data->meat != 0)
	{
		i = 0;
		while (i < data->nbphilo && !check_death(philo) && !check_eoeat(philo))
		{
			if ((ft_time() - (*philo)[i].data->stime)
				- (*philo)[i].feat >= data->die)
			{
				ft_print(philo, "%lld %d died\n");
				if (pthread_mutex_lock(&data->m_dead))
					return (-1);
				data->dead = 1;
				pthread_mutex_unlock(&data->m_dead);
			}
			i++;
		}
		usleep(1000);
	}
	return (0);
}

typedef void	*(*t_routine)(void *);

int	philocreate(t_philo **philo)
{
	int	i;

	i = 0;
	(*philo)->data->stime = ft_time();
	(*philo)->data->dead = 0;
	while (i < (*philo)->data->nbphilo)
	{
		if (pthread_mutex_init(&(*philo)[i].m_feat, NULL))
		{
			ft_clear(philo, i - 1, i);
			return (1);
		}
		if (pthread_create(&(*philo)[i].philosophe, NULL, (t_routine)routine,
			&(*philo)[i]))
		{
			ft_clear(philo, i, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*routine(t_philo *philo)
{
	// tableau int pour avoir que f[2] test 2 90000 200 200 1
	int	i;
	int	f1;
	int	f2;

	f1 = 0;
	f2 = 0;
	i = 0;
	pthread_mutex_lock(&philo->data->m_sync);
	pthread_mutex_unlock(&philo->data->m_sync);
	if (philo->philo_id % 2 == 1)
	{
		ft_msleep(&philo, 1);
	}
	while (!check_death(&philo) && philo->data->meat != 0
		&& !check_eoeat(&philo))
	{
		if (!check_death(&philo) && !check_eoeat(&philo))
			ft_print(&philo, "%lld %d is thinking\n");
		if (!check_death(&philo) && !check_eoeat(&philo))
		{
			f1 = 1;
			pthread_mutex_lock(philo->mutex_fork2);
			if (philo->data->nbphilo != 1)
				{
					f2 = 1;
					pthread_mutex_lock(&philo->mutex_fork);
				}
			if (!check_death(&philo) && !check_eoeat(&philo))
				ft_print(&philo, "%lld %d has taken a fork\n");
			// return (0); // fct prtege et destroy mutex
		}
		if (f1 && f2)
		{
			philo->feat = (ft_time() - philo->data->stime);
		}
		if (!check_death(&philo) && f1 && f2 && !check_eoeat(&philo))
		{
			ft_print(&philo, "%lld %d has taken a fork\n");
			ft_print(&philo, "%lld %d is eating\n");
			ft_msleep(&philo, philo->data->eat);
		}  // return (0); // fct prtege et destroy mutex
		if (f1)
			pthread_mutex_unlock(philo->mutex_fork2);
		if (f2)
			pthread_mutex_unlock(&philo->mutex_fork);
		if (philo->data->meat > 0 && (i + 1) == philo->data->meat && f1 && f2)
		{
			pthread_mutex_lock(&philo->data->m_eoeat);
			philo->data->eoeat += 1;
			pthread_mutex_unlock(&philo->data->m_eoeat);
		}
		if (!check_death(&philo) && (f1 && f2)
			&& !check_eoeat(&philo))
		{
			ft_print(&philo, "%lld %d is sleeping\n");
			ft_msleep(&philo, philo->data->sleep);
		}
		i++;
		while (!check_death(&philo) && (philo->data->nbphilo == 1 && i))
			usleep(150);
	}
	return (philo);
}

int	philojoin(t_philo **philo)
{
	int	i;

	i = 0;
	while (i < (*philo)->data->nbphilo
		&& pthread_join((*philo)[i].philosophe, NULL) == 0)
		i++;
	if (i == (*philo)->data->nbphilo)
		return (0);
	return (-1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong args, you need to put 4 or 5 args (only unsigned int)\n");
		return (1);
	}
	data = init_data(argv);
	if (!data.meat || !data.nbphilo || init_mutex(&data))
		return (1);
	philo = init_philo(&data);
	if (!philo || pthread_mutex_lock(&data.m_sync) || philocreate(&philo))
		return (1);
	pthread_mutex_unlock(&data.m_sync);
	if (setdeath(&data, &philo) || philojoin(&philo))
	{
		ft_clear(&philo, -1, data.nbphilo);
		return (3);
	}
	ft_clear(&philo, -1, data.nbphilo);
	return (0);
}
