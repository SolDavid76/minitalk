/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:40:24 by djanusz           #+#    #+#             */
/*   Updated: 2023/02/15 16:37:08 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_atoi(char *str)
{
	int	sign;
	int	res;
	int	i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		res *= 10;
		res += (str[i] - '0');
		i++;
	}
	return (sign * res);
}

int	main(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 4)
		return (1);
	i = 0;
	while (av[2][i])
	{
		j = 7;
		while (j + 1)
		{
			if (av[2][i] >> j & 1)
				kill(ft_atoi(av[1]), SIGUSR1);
			else
				kill(ft_atoi(av[1]), SIGUSR2);
			usleep(ft_atoi(av[3]));
			j--;
		}
		i++;
	}
	return (0);
}
