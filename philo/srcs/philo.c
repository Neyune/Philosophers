/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:32:46 by ereali            #+#    #+#             */
/*   Updated: 2021/11/11 21:04:18 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

long long ft_time(void)
{
	t_timeval now;
	unsigned long time;

	if (gettimeofday(&now, NULL) != 0)
	write(1, "ERROR\n", 6);
	time = ((now.tv_sec * 1000) + (now.tv_usec / 1000));
	return (time);
}

void ft_msleep(long long msec)
{

	long long timestamp;


	timestamp = ft_time();
	while(ft_time() - timestamp < msec)
		usleep(150);
}

typedef void *(*t_routine)(void *);

void    *Routine(t_philo *philo)
{
	int i;
	int f1;
	int f2;

	f1 = 0;
	f2 = 0;
	i = 0;
	while ((philo->data->meat == -1 && philo->data->dead == 0) || (i < philo->data->meat && philo->data->dead == 0))
	{
		if (philo->data->dead == 0 && !(philo->data->nbphilo == 1 && i >= 1))
			printf("%lld %d is thinking\n", (ft_time() - philo->data->stime), philo->philo_id);
		if ((philo->philo_id % 2 == 1 && philo->data->dead == 0) && !(philo->data->nbphilo == 1 && i >= 1))
		{
			f1 = 1;
			pthread_mutex_lock(philo->mutex_fork2);
			if (philo->data->dead == 0)
				printf("%lld %d has taken a fork\n", (ft_time() - philo->data->stime), philo->philo_id);
			// return (0); // fct prtege et destroy mutex
		}
		if (philo->philo_id % 2 == 0 && philo->data->dead == 0)
		{
			f2 = 1;
			pthread_mutex_lock(&philo->mutex_fork);
			if (philo->data->dead == 0)
				printf("%lld %d has taken a fork\n", (ft_time() - philo->data->stime), philo->philo_id);
			// return (0); // fct prtege et destroy mutex
		}
		if (philo->philo_id % 2 == 1 && philo->data->dead == 0 && philo->data->nbphilo > 1)
		{
			f2 = 1;
			pthread_mutex_lock(&philo->mutex_fork);
		}
		if (philo->philo_id % 2 == 0 && philo->data->dead == 0)
		{
			f1 = 1;
			pthread_mutex_lock(philo->mutex_fork2);
		}
		if (f1 && f2)
			philo->feat = (ft_time() - philo->data->stime);
		if (philo->data->dead == 0 && f1 && f2)
		{
			printf("%lld %d has taken a fork\n", (ft_time() - philo->data->stime), philo->philo_id);
			printf("%lld %d is eating\n", (ft_time() - philo->data->stime), philo->philo_id);
			ft_msleep(philo->data->eat);
		}  // return (0); // fct prtege et destroy mutex
		if ((f1 && philo->data->nbphilo != 1) || (f1 && philo->data->dead))
			pthread_mutex_unlock(philo->mutex_fork2);
		if (f2)
			pthread_mutex_unlock(&philo->mutex_fork);
		if (philo->data->dead == 0 && (f1 && f2))
		{
			printf("%lld %d is sleeping\n", (ft_time() - philo->data->stime), philo->philo_id);
			ft_msleep(philo->data->sleep);
		}
		i++;
	}
	while (philo->data->dead == 0 && (philo->data->nbphilo == 1 && i >= 1))
	{
	}
	philo->data->EOeat += 1;
	return (philo);
}

int main(int argc, char **argv)
{
	t_data  data;
	t_philo *philo;
	int i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (0);
	if (check_arg(argv, (int*)&data) == NULL)
	{
		if (data.meat == 0)
		return (0);
		printf("Wrong args you need to put 4 or 5 ags only unsigned int\n");
		return (-1);
	}
	data.dead = 0;
	data.EOeat = 0;
	philo = malloc(data.nbphilo * sizeof (*philo));
	if (philo == NULL)
	return (0);
	while (i < data.nbphilo)
	{
		philo[i].philo_id = i + 1;
		philo[i].feat = 0;
		philo[i].seat = 0;
		pthread_mutex_init(&philo[i].mutex_fork, NULL);
		if (i != data.nbphilo - 1)
		philo[i].mutex_fork2 = &philo[i + 1].mutex_fork;
		else
		philo[i].mutex_fork2 = &philo[0].mutex_fork;
		philo[i].data = &data;
		i++;
	}
	i = 0;
	data.stime = ft_time();
	while (i < data.nbphilo)
	{
		pthread_create(&philo[i].philosophe, NULL, (t_routine)Routine, &philo[i]);
		i++;
	}
	while (data.dead == 0 && data.EOeat != data.nbphilo && data.meat != 0)
	{
		i = 0;
		while (i < data.nbphilo && data.dead == 0 && data.EOeat != data.nbphilo)
		{
			if ((ft_time() - philo->data->stime) - philo[i].feat >= data.die)
			{
				data.dead = 1;
				printf("%lld %d died\n", (ft_time() - philo->data->stime), i + 1);
			}
			usleep(150);
			i++;
		}
		// printf("dead %d , EOeat %d , nbphilo %d , meat %d", data.dead, data.EOeat ,data.nbphilo, data.meat);

	}
	i = 0;
	while (i < data.nbphilo)
	{
		pthread_join(philo[i].philosophe, NULL);
		i++;
	}
	return (0);
}
