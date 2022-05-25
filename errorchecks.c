/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorchecks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:50:45 by jking-ye          #+#    #+#             */
/*   Updated: 2022/05/24 17:43:58 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checkintover(char *num)
{
	int		i;
	char	*c;
	int		test;

	i = ft_atoi(num);
	c = ft_itoa(i);
	test = ft_strcmp(num, c);
	free(c);
	if (test == 0)
		return (1);
	return (0);
}

int	errorcheck(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!(checkintover(argv[i])))
		{
			printf("Error\n");
			return (0);
		}
		if (argv[i][0] == '-')
		{
			printf("Error\n");
			return (0);
		}
		i++;
	}
	return (1);
}
