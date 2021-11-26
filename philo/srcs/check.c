/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 04:47:43 by ereali            #+#    #+#             */
/*   Updated: 2021/11/18 18:27:48 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->data->m_dead);
	if ((*philo)->data->dead == 1)
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
	if ((*philo)->data->eoeat == (*philo)->data->nbphilo)
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
	if (!check_eoeat(philo) && !check_death(philo))
	{
		printf(str, ft_time() - (*philo)->data->stime, (*philo)->philo_id);
	}
	pthread_mutex_unlock(&(*philo)->data->m_printf);
}

int	usefeat(t_philo **philo, int i, int nb)
{
	if (i == 0)
	{
		pthread_mutex_lock(&(*philo)->m_feat);
		(*philo)->feat = (ft_time() - (*philo)->data->stime);
		pthread_mutex_unlock(&(*philo)->m_feat);
	}
	if (i == 1)
	{
		pthread_mutex_lock(&(*philo)[nb].m_feat);
		if ((ft_time() - (*philo)->data->stime)
			- (*philo)[nb].feat >= (*philo)->data->die)
		{
			pthread_mutex_unlock(&(*philo)[nb].m_feat);
			return (1);
		}
		pthread_mutex_unlock(&(*philo)[nb].m_feat);
	}
	return (0);
}

void	increeoeat(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->data->m_eoeat);
	(*philo)->data->eoeat += 1;
	pthread_mutex_unlock(&(*philo)->data->m_eoeat);
}
