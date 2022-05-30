/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:29:29 by jking-ye          #+#    #+#             */
/*   Updated: 2022/05/30 15:24:47 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	getcurrentime(void)
{
	struct timeval	start_time;
	long long		cur;

	gettimeofday(&start_time, NULL);
	cur = start_time.tv_sec * 1000.0;
	cur += start_time.tv_usec / 1000.0;
	return (cur);
}

int	checkifdead(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->die);
	if (philo->info->isdead == 1)
	{
		pthread_mutex_unlock(&philo->info->die);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->die);
	return (0);
}

int	checkeatcount(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat_mutex);
	if (philo->eat_count == philo->info->n_eat && philo->info->n_eat != 0)
	{
		pthread_mutex_unlock(&philo->last_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_eat_mutex);
	return (0);
}

int	checklastate(t_philo *philo)
{
	msleep(1);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->current = getcurrentime();
	if (philo->current - philo->last_ate > philo->info->die_ms)
	{
		pthread_mutex_unlock(&philo->last_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_eat_mutex);
	return (0);
}
