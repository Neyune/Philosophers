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

int main(int argc, char **argv)
{
    t_data  data;

    if (argc != 5 && argc != 6)
        return (0);
    if (check_arg(argv, data.args) == NULL)
        return (-1);
    data.args[0] = *check_arg(argv, data.args);    
    if (argc == 5)
    {
    }
    if (argc == 6)
    {
    }
    return (0);
}
