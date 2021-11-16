
// #include "philo.h"
//
// typedef void *(*t_routine)(void *);
//
// void    *Routine(t_philo *philo)
// {
// 	int i;
// 	int f1;
// 	int f2;
// 	int eatenough;
//
// 	f1 = 0;
// 	f2 = 0;
// 	i = 0;
// 	eatenough = 0;
// 	while (philo->data->dead == 0 && philo->data->meat != 0 && philo->data->EOeat != philo->data->nbphilo)
// 	{
// 		if (philo->data->dead == 0 && !(philo->data->nbphilo == 1 && i >= 1))
// 			printf("%lld %d is thinking\n", (ft_time() - philo->data->stime), philo->philo_id);
// 		if ((philo->philo_id % 2 == 1 && philo->data->dead == 0) && !(philo->data->nbphilo == 1 && i >= 1))
// 		{
// 			f1 = 1;
// 			pthread_mutex_lock(philo->mutex_fork2);
// 			if (philo->data->dead == 0)
// 				printf("%lld %d has taken a fork\n", (ft_time() - philo->data->stime), philo->philo_id);
// 			// return (0); // fct prtege et destroy mutex
// 		}
// 		if (philo->philo_id % 2 == 0 && philo->data->dead == 0)
// 		{
// 			f2 = 1;
// 			pthread_mutex_lock(&philo->mutex_fork);
// 			if (philo->data->dead == 0)
// 				printf("%lld %d has taken a fork\n", (ft_time() - philo->data->stime), philo->philo_id);
// 			// return (0); // fct prtege et destroy mutex
// 		}
// 		if (philo->philo_id % 2 == 1 && philo->data->dead == 0 && philo->data->nbphilo > 1)
// 		{
// 			f2 = 1;
// 			pthread_mutex_lock(&philo->mutex_fork);
// 		}
// 		if (philo->philo_id % 2 == 0 && philo->data->dead == 0)
// 		{
// 			f1 = 1;
// 			pthread_mutex_lock(philo->mutex_fork2);
// 		}
// 		if (f1 && f2)
// 			philo->feat = (ft_time() - philo->data->stime);
// 		if (philo->data->dead == 0 && f1 && f2)
// 		{
// 			printf("%lld %d has taken a fork\n", (ft_time() - philo->data->stime), philo->philo_id);
// 			printf("%lld %d is eating\n", (ft_time() - philo->data->stime), philo->philo_id);
// 			ft_msleep(&philo->data, philo->data->eat);
// 		}  // return (0); // fct prtege et destroy mutex
// 		if ((f1 && philo->data->nbphilo != 1) || (f1 && philo->data->dead))
// 			pthread_mutex_unlock(philo->mutex_fork2);
// 		if (f2)
// 			pthread_mutex_unlock(&philo->mutex_fork);
// 		if (philo->data->dead == 0 && (f1 && f2))
// 		{
// 			printf("%lld %d is sleeping\n", (ft_time() - philo->data->stime), philo->philo_id);
// 			ft_msleep(&philo->data,philo->data->sleep);
// 		}
// 		i++;
// 		if (philo->data->meat > 0 && i >= philo->data->meat && eatenough == 0)
// 		{
// 			eatenough = 1;
// 			philo->data->EOeat += 1;
// 		}
// 	}
// 	while (philo->data->dead == 0 && (philo->data->nbphilo == 1 && i >= 1))
// 	{
// 		usleep(150);
// 	}
// 	return (philo);
// }

// 16/11
// void    *Routine(t_philo *philo)
// {
// 	// tableau int pour avoir que f[2] test 2 90000 200 200 1
// 	int i;
// 	int f1;
// 	int f2;
//
// 	f1 = 0;
// 	f2 = 0;
// 	i = 0;
// 	pthread_mutex_lock(&philo->data->m_sync);
// 	pthread_mutex_unlock(&philo->data->m_sync);
// 	if (philo->philo_id % 2 == 1)
// 		usleep(150);
// 	while (philo->data->dead == 0 && philo->data->meat != 0 && philo->data->EOeat != philo->data->nbphilo)
// 	{
// 		if (philo->data->dead == 0 && !(philo->data->nbphilo == 1 && i >= 1) && philo->data->EOeat != philo->data->nbphilo)
// 			printf("%lld %d is thinking\n", (ft_time() - philo->data->stime), philo->philo_id);
// 		if (philo->philo_id % 2 == 0 && philo->data->dead == 0 && philo->data->EOeat != philo->data->nbphilo)
// 		{
// 			f2 = 1;
// 			f1 = 1;
// 			pthread_mutex_lock(&philo->mutex_fork);
// 			if (philo->data->dead == 0 && philo->data->EOeat != philo->data->nbphilo)
// 				printf("%lld %d has taken a fork\n", (ft_time() - philo->data->stime), philo->philo_id);
// 			pthread_mutex_lock(philo->mutex_fork2);
// 			// return (0); // fct prtege et destroy mutex
// 		}
// 		if ((philo->philo_id % 2 == 1 && philo->data->dead == 0) && !(philo->data->nbphilo == 1 && i >= 1))
// 		{
// 			f1 = 1;
// 			pthread_mutex_lock(philo->mutex_fork2);
// 			if (philo->data->dead == 0 && philo->data->EOeat != philo->data->nbphilo)
// 				printf("%lld %d has taken a fork\n", (ft_time() - philo->data->stime), philo->philo_id);
// 			if (philo->data->nbphilo != 1)
// 				{
// 				f2 = 1;
// 				pthread_mutex_lock(&philo->mutex_fork);
// 				}
// 			// return (0); // fct prtege et destroy mutex
// 		}
// 		if (f1 && f2)
// 			philo->feat = (ft_time() - philo->data->stime);
// 		if (philo->data->dead == 0 && f1 && f2 && philo->data->EOeat != philo->data->nbphilo)
// 		{
// 			printf("%lld %d has taken a fork\n", (ft_time() - philo->data->stime), philo->philo_id);
// 			printf("%lld %d is eating\n", (ft_time() - philo->data->stime), philo->philo_id);
// 			ft_msleep(&philo->data, philo->data->eat);
// 		}  // return (0); // fct prtege et destroy mutex
// 		if ((f1 && philo->data->nbphilo != 1) || (f1 && philo->data->dead))
// 			pthread_mutex_unlock(philo->mutex_fork2);
// 		if (f2)
// 			pthread_mutex_unlock(&philo->mutex_fork);
// 		if (philo->data->meat > 0 && (i + 1) == philo->data->meat && f1 && f2)
// 		{
// 			pthread_mutex_lock(&philo->data->m_EOeat);
// 			philo->data->EOeat += 1;
// 			pthread_mutex_unlock(&philo->data->m_EOeat);
// 		}
// 		if (philo->data->dead == 0 && (f1 && f2) && philo->data->EOeat != philo->data->nbphilo)
// 		{
// 			printf("%lld %d is sleeping\n", (ft_time() - philo->data->stime), philo->philo_id);
// 			ft_msleep(&philo->data,philo->data->sleep);
// 		}
// 		i++;
// 	}
// 	while (philo->data->dead == 0
// 		&& (philo->data->nbphilo == 1 && i >= 1))
// 		usleep(150);
// 		//safe car fixe
// 	return (philo);
// }
