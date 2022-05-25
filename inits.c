/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:50:53 by jking-ye          #+#    #+#             */
/*   Updated: 2022/05/25 15:19:19 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_philo *philos, int argc, char **argv)
{
	int	i;
	int	num_philo;

	i = 0;
	num_philo = ft_atoi(argv[1]);
	while (i < num_philo)
	{
		philos[i].info.num_philo = ft_atoi(argv[1]);
		philos[i].info.die_ms = ft_atoi(argv[2]);
		philos[i].info.eat_ms = ft_atoi(argv[3]);
		philos[i].info.sleep_ms = ft_atoi(argv[4]);
		philos[i].eat_count = 0;
		if (argc == 6)
			philos[i].info.num_eat = ft_atoi(argv[5]);
		if (i + 1 != num_philo)
			philos[i].next_philo = &philos[i + 1];
		else
			philos[i].next_philo = &philos[0];
		philos[i].id = i + 1;
		i++;
	}
}

void	msleep(long i)
{
	usleep(i * 1000);
}

void	philo_action(char *str, t_philo *philo, char *color)
{
	struct timeval	timestamp;
	long long		current;

	usleep(300);
	if (*philo->isdead != 1)
	{
		pthread_mutex_lock(philo->print);
		gettimeofday(&timestamp, NULL);
		current = timestamp.tv_sec * 1000.0;
		current += timestamp.tv_usec / 1000.0;
		if (ft_strcmp("is eating", str) == 0)
			philo->begin = current;
		printf("%s%lld %d %s\n", color, current, philo->id, str);
		pthread_mutex_unlock(philo->print);
	}
}
