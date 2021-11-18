/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:35:05 by ereali            #+#    #+#             */
/*   Updated: 2021/11/18 06:45:35 by ereali           ###   ########.fr       */
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

typedef struct timeval	t_timeval;

typedef struct s_data
{
	int				nbphilo;
	int				die;
	int				eat;
	int				sleep;
	int				meat;
	long long		stime;
	pthread_mutex_t	m_sync;
	pthread_mutex_t	m_eoeat;
	int				eoeat;
	pthread_mutex_t	m_dead;
	int				dead;
	pthread_mutex_t	m_printf;
}				t_data;

typedef struct s_philo
{
	int				philo_id;
	pthread_mutex_t	m_feat;
	long long int	feat;
	long long int	seat;
	pthread_t		philosophe;
	pthread_mutex_t	mutex_fork;
	pthread_mutex_t	*mutex_fork2;
	t_data			*data;
}					t_philo;

int			ft_atoi(char *str);
long int	ft_atol(char *str);
long long	ft_time(void);
int			*check_arg(char **argv, int *args);
int			check_death(t_philo **philo);
int			check_eoeat(t_philo **philo);
void		ft_print(t_philo **philo, char *str);
void		ft_msleep(t_philo **philo, long long msec);

void		ft_clear(t_philo **philo, int j, int k);

t_data		init_data(char **argv);
int			init_mutex(t_data *data);
t_philo		*init_philo(t_data *data);

void		*routine(t_philo *philo);
#endif
