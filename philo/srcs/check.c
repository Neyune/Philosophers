/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 04:47:43 by ereali            #+#    #+#             */
/*   Updated: 2021/11/18 06:51:54 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//creer ft check feat 

int	check_death(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->data->m_dead);
	if((*philo)->data->dead == 1)
	{
		pthread_mutex_unlock(&(*philo)->data->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&(*philo)->data->m_dead);
	return (0);
}

int	check_eoeat(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->data->m_eoeat);
	if((*philo)->data->eoeat == (*philo)->data->nbphilo)
	{
		pthread_mutex_unlock(&(*philo)->data->m_eoeat);
		return (1);
	}
	pthread_mutex_unlock(&(*philo)->data->m_eoeat);
	return (0);
}

void	ft_print(t_philo **philo, char *str)
{
	pthread_mutex_lock(&(*philo)->data->m_printf);
	if(!check_death(philo) && !check_eoeat(philo))
	{
		printf(str, ft_time() - (*philo)->data->stime, (*philo)->philo_id);
	}
	pthread_mutex_unlock(&(*philo)->data->m_printf);
}
