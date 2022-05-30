/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:04:28 by jking-ye          #+#    #+#             */
/*   Updated: 2022/05/30 15:43:13 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos)
{
	int	i;
	int	num_philo;

	i = 0;
	num_philo = philos->info->num_philo;
	while (i < num_philo)
	{
		philos[i].eat_count = 0;
		if (i + 1 != num_philo)
			philos[i].next_philo = &philos[i + 1];
		else
			philos[i].next_philo = &philos[0];
		philos[i].id = i + 1;
		pthread_create(&philos[i].philo, NULL, &dosmth, &philos[i]);
		pthread_create(&philos[i].death, NULL, &death_tracker, &philos[i]);
		pthread_mutex_init(&philos[i].fork, NULL);
		pthread_mutex_init(&philos[i].eat, NULL);
		pthread_mutex_init(&philos[i].last_eat_mutex, NULL);
		i++;
	}
	pthread_mutex_lock(&philos->info->die);
	philos->info->start = 1;
	pthread_mutex_unlock(&philos->info->die);
}

void	*death_tracker(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	waitphilo(philo);
	while (1)
	{
		msleep(2);
		if (checkifdead(philo))
			return (0);
		if (checkeatcount(philo))
			return (0);
		if (checklastate(philo))
		{
			philo_action("died", philo, KRED);
			pthread_mutex_lock(&philo->info->die);
			philo->info->isdead = 1;
			pthread_mutex_unlock(&philo->info->die);
			return (0);
		}
	}
	return (0);
}

void	routine(t_philo *philos)
{
	philo_action("is thinking", philos, KBLU);
	pthread_mutex_lock(&philos->fork);
	philo_action("has taken a fork", philos, KGRN);
	if (philos->info->num_philo == 1)
	{
		msleep(philos->info->die_ms + 2);
		pthread_mutex_unlock(&philos->fork);
	}
	pthread_mutex_lock(&philos->next_philo->fork);
	philo_action("has taken a fork", philos, KGRN);
	// pthread_mutex_lock(&philos->last_eat_mutex);
	philo_action("is eating", philos, KCYN);
	pthread_mutex_lock(&philos->last_eat_mutex);
	philos->eat_count++;
	pthread_mutex_unlock(&philos->last_eat_mutex);
	msleep(philos->info->eat_ms);
	pthread_mutex_unlock(&philos->fork);
	pthread_mutex_unlock(&philos->next_philo->fork);
	philo_action("is sleeping", philos, KMAG);
	msleep(philos->info->sleep_ms - 1);
}

void	*dosmth(void *arg)
{
	t_philo			*philos;

	philos = (t_philo *)arg;
	waitphilo(philos);
	if (philos->id % 2 == 0)
		msleep(1);
	pthread_mutex_lock(&philos->last_eat_mutex);
	philos->last_ate = getcurrentime();
	pthread_mutex_unlock(&philos->last_eat_mutex);
	while (1)
	{
		routine(philos);
		if (checkifdead(philos))
			return (0);
		if (checkeatcount(philos))
			return (0);
		// routine(philos);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	int				i;

	if (argc > 4 && argc < 7)
	{
		if (errorcheck(argc, argv) == 0)
			return (0);
		philos = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
		init_table(philos, argc, argv);
		init_philos(philos);
		i = 0;
		while (i < philos->info->num_philo)
		{
			pthread_join(philos[i].philo, NULL);
			pthread_join(philos[i].death, NULL);
			pthread_mutex_destroy(&philos[i].fork);
			pthread_mutex_destroy(&philos[i].eat);
			pthread_mutex_destroy(&philos[i].last_eat_mutex);
			i++;
		}
		free(philos);
	}
	return (0);
}
