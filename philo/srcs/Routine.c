/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:31:54 by ereali            #+#    #+#             */
/*   Updated: 2021/11/18 21:24:53 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	takefork(t_philo **philo)
{
	int	f2;

	f2 = 0;
	if (!check_death(philo) && !check_eoeat(philo))
	{
		// if ((*philo)->philo_id != 1)
		// {
			pthread_mutex_lock(&(*philo)->mutex_fork);
			f2 += 1;
		// }
		if ((*philo)->data->nbphilo != 1)
		{
			pthread_mutex_lock((*philo)->mutex_fork2);
			f2 += 1;
		}
		// if ((*philo)->philo_id == 1)
		// {
			// pthread_mutex_lock(&(*philo)->mutex_fork);
			// f2 += 1;
		// }
		ft_print(philo, "%lld %d has taken a fork\n");
	}
	return (f2);
}

void	eat(t_philo **philo, int nb)
{
	if (nb == 2)
	{
		usefeat(philo, 0, 0);
		ft_print(philo, "%lld %d has taken a fork\n");
		ft_print(philo, "%lld %d is eating\n");
		ft_msleep(philo, (*philo)->data->eat);
		pthread_mutex_unlock((*philo)->mutex_fork2);
	}
}

void	ft_printsleep(t_philo **philo, int nb)
{
	if (nb == 2)
	{
		ft_print(philo, "%lld %d is sleeping\n");
		ft_msleep(philo, (*philo)->data->sleep);
	}
}
