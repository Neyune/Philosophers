/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:32:46 by ereali            #+#    #+#             */
/*   Updated: 2021/11/18 21:01:03 by ereali           ###   ########.fr       */
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
			if (usefeat(philo, 1, i))
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

		if (pthread_create(&(*philo)[i].philosophe, NULL, (t_routine)routine,
			&(*philo)[i]))
		{
			pthread_mutex_lock(&(*philo)->data->m_eoeat);
			(*philo)->data->eoeat = (*philo)->data->nbphilo;
			pthread_mutex_unlock(&(*philo)->data->m_eoeat);
			pthread_mutex_unlock(&(*philo)->data->m_coor);
			ft_clear(philo, -1, i, i);
			return (1);
		}
		if (pthread_mutex_init(&(*philo)[i].m_feat, NULL))
		{
			pthread_mutex_lock(&(*philo)->data->m_eoeat);
			(*philo)->data->eoeat = (*philo)->data->nbphilo;
			pthread_mutex_unlock(&(*philo)->data->m_eoeat);
			pthread_mutex_unlock(&(*philo)->data->m_coor);
			ft_clear(philo, -1 , i, i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*routine(t_philo *philo)
{
	int	i;
	int	f2;

	i = 0;
	pthread_mutex_lock(&philo->data->m_coor);
	pthread_mutex_unlock(&philo->data->m_coor);
	if (philo->philo_id % 2 == 0)
		ft_msleep(&philo, 1);
	while (!check_eoeat(&philo) && philo->data->meat != 0
		&& !check_death(&philo))
	{
		ft_print(&philo, "%lld %d is thinking\n");
		f2 = takefork(&philo);
		eat(&philo, f2);
		if (f2 > 0)
			pthread_mutex_unlock(&(philo)->mutex_fork);
		if (philo->data->meat > 0 && (i + 1) == philo->data->meat && f2 == 2)
			increeoeat(&philo);
		ft_printsleep(&philo, f2);
		i++;
		while (!check_death(&philo) && (philo->data->nbphilo == 1 && i))
			usleep(150);
	}

	return (philo);
}

int	philojoin(t_philo **philo, int limit)
{
	int	i;
	int error;

	i = 0;
	error = 0;
	while (i < limit)
	{
		if (pthread_join((*philo)[i].philosophe, NULL) != 0)
			error++;
		i++;
	}
	if (i == limit)
		return (0);
	return (error);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
	{
		write(2,"Wrong args, you need to put 4 or 5 args (only unsigned int)\n"
		, 60);
		return (1);
	}
	data = init_data(argv);
	if (!data.meat || !data.nbphilo  || init_mutex(&data))
		return (1);
	philo = init_philo(&data);
	if (!philo || pthread_mutex_lock(&data.m_coor) || philocreate(&philo))
		return (1);
	pthread_mutex_unlock(&data.m_coor);
	if (setdeath(&data, &philo))
	{
		ft_clear(&philo, -1, data.nbphilo, data.nbphilo);
		return (3);
	}
	ft_clear(&philo, -1, data.nbphilo, data.nbphilo);
	return (0);
}
