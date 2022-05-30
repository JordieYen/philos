/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:50:53 by jking-ye          #+#    #+#             */
/*   Updated: 2022/05/30 15:36:04 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_philo *philos, int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table));
	table->num_philo = ft_atoi(argv[1]);
	table->die_ms = ft_atoi(argv[2]);
	table->eat_ms = ft_atoi(argv[3]);
	table->sleep_ms = ft_atoi(argv[4]);
	if (argc == 6)
		table->n_eat = ft_atoi(argv[5]);
	table->isdead = 0;
	table->start = 0;
	pthread_mutex_init(&table->die, NULL);
	pthread_mutex_init(&table->print, NULL);
	i = 0;
	while (i < table->num_philo)
	{
		philos[i].info = table;
		i++;
	}
}

void	waitphilo(t_philo *philo)
{
	msleep(2 * philo->info->num_philo);
	pthread_mutex_lock(&philo->info->die);
	while (philo->info->start == 0)
	{
		usleep(500);
	}
	pthread_mutex_unlock(&philo->info->die);
	msleep(philo->info->num_philo / 3);
}

void	msleep(long timetosleep)
{
	struct timeval	current;
	long long		start_time;
	long long		end_time;

	gettimeofday(&current, NULL);
	start_time = (current.tv_sec * 1000);
	start_time += (current.tv_usec / 1000);
	end_time = start_time + timetosleep;
	while (start_time < end_time)
	{
		gettimeofday(&current, NULL);
		start_time = (current.tv_sec * 1000);
		start_time += (current.tv_usec / 1000);
		usleep(50);
		if (start_time > end_time)
			break ;
	}
}

void	philo_action(char *str, t_philo *philo, char *color)
{
	struct timeval	timestamp;
	long long		current;

	pthread_mutex_lock(&philo->info->die);
	if (philo->info->isdead != 1)
	{
		pthread_mutex_unlock(&philo->info->die);
		pthread_mutex_lock(&philo->info->print);
		gettimeofday(&timestamp, NULL);
		current = timestamp.tv_sec * 1000.0;
		current += timestamp.tv_usec / 1000.0;
		if (ft_strcmp("is eating", str) == 0)
		{
			pthread_mutex_lock(&philo->last_eat_mutex);
			philo->last_ate = current;
			pthread_mutex_unlock(&philo->last_eat_mutex);
		}
		printf("%s%lld %d %s\n", color, current, philo->id, str);
		pthread_mutex_unlock(&philo->info->print);
	}
	pthread_mutex_unlock(&philo->info->die);
}
