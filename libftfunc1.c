/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:45:31 by jking-ye          #+#    #+#             */
/*   Updated: 2022/05/16 11:45:36 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	countnum(long n)
{
	int	i;

	i = 0;
	if (n > 0)
	{
		while (n > 0)
		{
			n = n / 10;
			i++;
		}
	}
	else
	{
		while (n < 0)
		{
			n = n / 10;
			i++;
		}
	}
	return (i);
}

static	char	*numtostring(int i, long k, char *ptr)
{
	int	isneg;

	isneg = 0;
	if (k < 0)
	{
		k = k * -1;
		isneg = 1;
	}
	ptr[i] = '\0';
	i--;
	if (k == 0)
	{
		ptr[0] = 48;
		return (ptr);
	}
	while (i >= 0)
	{
		if (isneg == 1 && i == 0)
			ptr[i] = '-';
		else
			ptr[i] = 48 + (k % 10);
		k = k / 10;
		i--;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		i;
	long	k;

	i = 0;
	k = n;
	if (k < 0)
		i = 1;
	if (n == 0)
	{
		ptr = malloc(2);
		ptr = numtostring(1, 0, ptr);
	}
	else
	{
		ptr = malloc(countnum(k) + i + 1);
		if (!ptr)
			return (0);
		ptr = numtostring(countnum(k) + i, k, ptr);
	}
	return (ptr);
}
