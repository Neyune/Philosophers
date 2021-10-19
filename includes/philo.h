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
# define PHILO 0
# define TTODIE 1
# define TTOEAT 2
# define TTOSLEEP 3
# define TMUSTEAT 4

typedef struct s_data
{
    int args[5];
}				t_data;

int         ft_atoi(char *str);
long int	ft_atol(char *str);
#endif
