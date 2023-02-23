/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:40:24 by djanusz           #+#    #+#             */
/*   Updated: 2023/02/23 11:54:02 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_pause;

void	handle(int signal)
{
	if (signal == SIGUSR1)
		g_pause = 0;
	if (signal == SIGUSR2)
	{
		write(1, "SUCCESS\n", 8);
		exit(0);
	}
}

void	ft_send_char(int pid, char c)
{
	int	time;
	int	i;

	i = 7;
	while (i + 1)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		time = 0;
		while (g_pause)
		{
			if (time++ == TIMEOUT)
			{
				write(1, "TIMEOUT\n", 9);
				exit(1);
			}
			sleep(1);
		}
		g_pause = 1;
		i--;
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3)
		return (1);
	signal(SIGUSR1, handle);
	signal(SIGUSR2, handle);
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		return (1);
	g_pause = 1;
	i = 0;
	while (av[2][i])
		ft_send_char(pid, av[2][i++]);
	ft_send_char(pid, '\0');
	return (0);
}
