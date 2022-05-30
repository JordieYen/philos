/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:45:21 by jking-ye          #+#    #+#             */
/*   Updated: 2022/05/30 15:20:57 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

typedef struct s_table
{
	int				num_philo;
	int				die_ms;
	int				eat_ms;
	int				sleep_ms;
	int				n_eat;
	int				isdead;
	int				start;
	pthread_mutex_t	die;
	pthread_mutex_t	print;
}	t_table;

typedef struct s_philo
{
	pthread_t		philo;
	pthread_t		death;
	pthread_mutex_t	fork;
	pthread_mutex_t	eat;
	pthread_mutex_t	last_eat_mutex;
	long long		last_ate;
	long long		current;
	int				id;
	int				eat_count;
	t_table			*info;
	struct s_philo	*next_philo;
}	t_philo;

void		init_table(t_philo *philos, int argc, char **argv);
void		init_philos(t_philo *philos);
void		msleep(long i);
int			checklastate(t_philo *philo);
void		philo_action(char *str, t_philo *philo, char *color);
void		*death_tracker(void *arg);
void		routine(t_philo *philos);
void		*dosmth(void *arg);
void		philosophise(t_philo *philos);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
char		**ft_split(const char *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isdigit(int c);
void		freearg(char **arg);
int			errorcheck(int argc, char **argv);
long long	getcurrentime(void);
void		waitphilo(t_philo *philo);
int			checkifdead(t_philo *philo);
int			checkeatcount(t_philo *philo);
int			main(int argc, char **argv);

#endif