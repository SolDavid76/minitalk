/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:43:39 by djanusz           #+#    #+#             */
/*   Updated: 2023/02/24 11:48:22 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_receve_str(int signal, siginfo_t *info, void *context)
{
	static char	*str = NULL;
	static int	c = 0;
	static int	n = 7;

	(void)context;
	c += (signal == SIGUSR1) << n--;
	if (n == -1)
	{
		str = ft_strjoin(str, c);
		if (!str)
			exit(1);
		if (c == '\0')
		{
			write(1, str, ft_strlen(str));
			write(1, "\n", 1);
			free(str);
			str = NULL;
			kill(info->si_pid, SIGUSR2);
		}
		c = 0;
		n = 7;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	data;

	sigemptyset(&data.sa_mask);
	data.sa_flags = SA_SIGINFO;
	data.sa_sigaction = ft_receve_str;
	write(1, "PID : ", 6);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sigaction(SIGUSR1, &data, 0);
	sigaction(SIGUSR2, &data, 0);
	while (1)
	{
	}
}
