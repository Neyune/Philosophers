/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:35:05 by ereali            #+#    #+#             */
/*   Updated: 2021/11/08 21:29:03 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval  t_timeval;

typedef struct  s_data
{
    int         nbphilo;
    int         die;
    int         eat;
    int         sleep;
    int         meat;
    long long   stime;
    int         EOeat;
	int			dead;
}				t_data;

typedef struct  s_philo
{
    unsigned int	philo_id;
	long long int   feat;
	long long int	seat;
    pthread_t		philosophe;
    pthread_mutex_t	mutex_fork;
    pthread_mutex_t	*mutex_fork2;
    t_data			*data;
}               t_philo;

int         ft_atoi(char *str);
long int    ft_atol(char *str);
#endif
