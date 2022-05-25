/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:45:28 by jking-ye          #+#    #+#             */
/*   Updated: 2022/05/16 11:45:29 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freearg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9' ))
		return (0);
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		c1 = s1[i];
		c2 = s2[i++];
		if ((c1 - c2) != 0)
			return (c1 - c2);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		negative;
	long	output;

	i = 0;
	output = 0;
	negative = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		output = output * 10 + (str[i] - '0');
		i++;
		if (output * negative > 2147483647)
			return (-1);
		else if (output * negative < -2147483648)
			return (0);
	}
	return (output * negative);
}
