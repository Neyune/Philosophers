/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:32:46 by ereali            #+#    #+#             */
/*   Updated: 2021/10/19 02:04:45 by ereali           ###   ########.fr       */
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

typedef void *(*t_routine)(void *);

void    *Routine(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->data->meat)
    {
        pthread_mutex_lock(philo->mutex_fork2);
        printf("%d has taken a fork\n", philo->philo_id);
        pthread_mutex_lock(&philo->mutex_fork);
        printf("%d has taken a fork\n", philo->philo_id);
            // return (0); // fct prtege et destroy mutex
        printf("%d is eating\n", philo->philo_id);
        usleep(philo->data->eat * 1000);
        pthread_mutex_unlock(philo->mutex_fork2);
            // return (0); // fct prtege et destroy mutex
        pthread_mutex_unlock(&philo->mutex_fork);
        i++;
    }
    printf("%d is sleeping\n", philo->philo_id);
    usleep(philo->data->sleep * 1000);
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
        return (-1); 
    philo = malloc(data.nbphilo * sizeof (*philo));
    if (philo == NULL)
        return (0);    
    while (i < data.nbphilo)
    {
        philo[i].philo_id = i;
        pthread_mutex_init(&philo[i].mutex_fork, NULL);   
        if (i != data.nbphilo - 1)
            philo[i].mutex_fork2 = &philo[i + 1].mutex_fork; 
        else
            philo[i].mutex_fork2 = &philo[0].mutex_fork; 
        philo[i].data = &data;
        i++;
    }
    i = 0;

    while (i < data.nbphilo)
    {
        pthread_create(&philo[i].philosophe, NULL, (t_routine)Routine, &philo[i]);
        i++;
    }
    i = 0;
    while (i < data.nbphilo)
    {
        pthread_join(philo[i].philosophe, NULL);
        i++;
    }
    return (0);
}

