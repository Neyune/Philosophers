/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:35:05 by ereali            #+#    #+#             */
/*   Updated: 2021/10/19 01:39:32 by ereali           ###   ########.fr       */
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
// # define PHILO 0
// # define TTODIE 1
// # define TTOEAT 2
// # define TTOSLEEP 3
// # define TMUSTEAT 4

typedef struct timeval  t_timeval;

typedef struct  s_data
{
    int         nbphilo;
    int         die;
    int         eat;
    int         sleep;
    int         meat;
    long long   stime;
    int         feat;
    int         seat;
    int         EOeat;
}				t_data;

typedef struct  s_philo
{
    unsigned int    philo_id;
    pthread_t       philosophe;
    pthread_mutex_t mutex_fork;
    pthread_mutex_t *mutex_fork2;
    t_data          *data;
}               t_philo;

int         ft_atoi(char *str);
long int    ft_atol(char *str);
#endif
