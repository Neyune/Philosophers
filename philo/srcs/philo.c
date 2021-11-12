/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:32:46 by ereali            #+#    #+#             */
/*   Updated: 2021/11/12 03:17:52 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *init_philo(t_data *data)
{
	int i;
	t_philo *philo;

	i = 0;
	data->dead = 0;
	data->EOeat = 0;
	philo = malloc(data->nbphilo * sizeof (*philo));
	if (philo == NULL)
	return (0);
	while (i < data->nbphilo)
	{
		philo[i].philo_id = i + 1;
		philo[i].feat = 0;
		philo[i].seat = 0;
		pthread_mutex_init(&philo[i].mutex_fork, NULL);
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

typedef void *(*t_routine)(void *);

void    *Routine(t_philo *philo)
{
	// tableau int pour avoir que f[2]
	int i;
	int f1;
	int f2;
	int eatenough;

	f1 = 0;
	f2 = 0;
	i = 0;
	eatenough = 0;
	while (philo->data->dead == 0 && philo->data->meat != 0 && philo->data->EOeat != philo->data->nbphilo)
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
			ft_msleep(&philo->data, philo->data->eat);
		}  // return (0); // fct prtege et destroy mutex
		if ((f1 && philo->data->nbphilo != 1) || (f1 && philo->data->dead))
			pthread_mutex_unlock(philo->mutex_fork2);
		if (f2)
			pthread_mutex_unlock(&philo->mutex_fork);
		if (philo->data->dead == 0 && (f1 && f2))
		{
			printf("%lld %d is sleeping\n", (ft_time() - philo->data->stime), philo->philo_id);
			ft_msleep(&philo->data,philo->data->sleep);
		}
		i++;
		if (philo->data->meat > 0 && i >= philo->data->meat && eatenough == 0)
		{
			eatenough = 1;
			philo->data->EOeat += 1;
		}
	}
	while (philo->data->dead == 0 && (philo->data->nbphilo == 1 && i >= 1))
	{
		usleep(150);
	}
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
		printf("Wrong args you need to put 4 or 5 ags only unsigned int\n");
		return (-1);
	}
	if (data.meat == 0)
		return (0);
	philo = init_philo(&data);
	i = 0;
	// creer mutex synch
	while (i < data.nbphilo)
	{
		pthread_create(&philo[i].philosophe, NULL, (t_routine)Routine, &philo[i]);
		i++;
	}
	// unlock mutex synch (test rapiditer d'un pthread create face a lock unlock) faire un usleep avant et apres
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
	}
	i = 0;
	while (i < data.nbphilo && pthread_join(philo[i].philosophe, NULL) == 0)
		i++;
	free(philo);
	return (0);
}
