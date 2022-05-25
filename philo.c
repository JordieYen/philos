/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:51:05 by jking-ye          #+#    #+#             */
/*   Updated: 2022/05/25 15:24:07 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_tracker(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	msleep(philo->info.die_ms + 100);
	while (1)
	{
		usleep(1000);
		if (*philo->isdead == 1)
			return (0);
		gettimeofday(&philo->cur_time, NULL);
		philo->current = philo->cur_time.tv_sec * 1000.0;
		philo->current += philo->cur_time.tv_usec / 1000.0;
		if (philo->eat_count == philo->info.num_eat && philo->info.num_eat != 0)
			return (0);
		if (philo->current - philo->begin > philo->info.die_ms)
		{
			pthread_mutex_lock(philo->die);
			philo_action("died", philo, KRED);
			*philo->isdead = 1;
			msleep(philo->info.die_ms);
			pthread_mutex_unlock(philo->die);
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
	if (philos->info.num_philo == 1)
	{
		pthread_mutex_unlock(&philos->fork);
		msleep(philos->info.die_ms);
	}
	if (philos->next_philo != NULL)
		pthread_mutex_lock(&philos->next_philo->fork);
	philo_action("has taken a fork", philos, KGRN);
	philo_action("is eating", philos, KCYN);
	philos->eat_count++;
	msleep(philos->info.eat_ms - 1);
	pthread_mutex_unlock(&philos->fork);
	pthread_mutex_unlock(&philos->next_philo->fork);
	philo_action("is sleeping", philos, KMAG);
	msleep(philos->info.sleep_ms - 1);
}

void	*dosmth(void *arg)
{
	t_philo			*philos;

	philos = (t_philo *)arg;
	msleep(philos->info.die_ms);
	if (philos->id % 2 == 0)
		usleep(800);
	gettimeofday(&philos->start_time, NULL);
	philos->begin = philos->start_time.tv_sec * 1000.0;
	philos->begin += philos->start_time.tv_usec / 1000.0;
	while (1)
	{
		if (*philos->isdead == 1)
			return (0);
		if (philos->eat_count == philos->info.num_eat
			&& philos->info.num_eat != 0)
			return (0);
		routine(philos);
		if (*philos->isdead == 1)
			return (0);
	}
	return (0);
}

void	philosophise(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].info.num_philo)
	{
		if (pthread_create(&philos[i].philo, NULL, &dosmth, &philos[i]) != 0)
			perror("Error at creating thread");
		if (pthread_create(&philos[i].death, NULL,
				&death_tracker, &philos[i]) != 0)
			perror("Error at creating thread");
		pthread_mutex_init(&philos[i].fork, NULL);
		i++;
	}
	i = 0;
	while (i < philos->info.num_philo)
	{
		if (pthread_join(philos[i].philo, NULL) != 0)
			perror("Error at joining thread");
		if (pthread_join(philos[i].death, NULL) != 0)
			perror("Error at joining thread");
		pthread_mutex_destroy(&philos[i].fork);
		i++;
	}
	free(philos);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	die;
	pthread_mutex_t	print;
	int				i;
	int				isdead;

	if (argc > 4 && argc < 7)
	{
		if (errorcheck(argc, argv) == 0)
			return (0);
		philos = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
		pthread_mutex_init(&die, NULL);
		pthread_mutex_init(&print, NULL);
		init_table(philos, argc, argv);
		i = 0;
		while (i < philos[0].info.num_philo)
		{
			philos[i].isdead = &isdead;
			philos[i].print = &print;
			philos[i].die = &die;
			i++;
		}
		philosophise(philos);
	}
	return (0);
}
